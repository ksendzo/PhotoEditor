package PhotoEditor;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.*;
import java.util.Iterator;

import static java.awt.image.BufferedImage.TYPE_INT_ARGB;

public class myLayer {
    private BufferedImage img;
    private boolean isActive = true;


    public myLayer(String path){
        try {
            File f;
            if(path.contains(":\\"))
                f = new File(path);
            else
                f = new File("C:\\Users\\Ksendzo\\IdeaProjects\\POOP_PhotoEditor\\src\\PhotoEditor\\" + path);

            if(path.contains(".bmp"))
                img = ImageIO.read(f);
            if(path.contains(".pam"))
                fromPAM(path);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void fromPAM(String path) {


        try {
            int width = 0, height = 0;

            FileInputStream fis = new FileInputStream(path);

            for(int i = 0; i < 9; i++)
                fis.read();
            int a;
            while((a = fis.read()) != 10)
                width = width*10 + a - '0';

            for(int i = 0; i < 7; i++)
                fis.read();

            while((a = fis.read()) != 10)
                height = height*10 + a - '0';

            img = new BufferedImage(width, height, TYPE_INT_ARGB);
            for(int i = 0; i < 45; i++)
                fis.read();

            for(int y = 0; y < height; y++)
                for (int x = 0; x < width; x++){
                    int r = fis.read();
                    int g = fis.read();
                    int b = fis.read();
                    int al = fis.read();
                    img.setRGB(x, y, (new Color(r,g,b,al)).getRGB());
                }
            fis.close();

        } catch (IOException e) {
            e.printStackTrace();
        }





    }

    public myLayer(JSONObject jsonObject){
        isActive = (boolean)jsonObject.get("active");

        JSONArray heightArray = (JSONArray)jsonObject.get("matrix");
        img = new BufferedImage(((JSONArray)heightArray.get(0)).size(), heightArray.size(), TYPE_INT_ARGB);
        for(int y = 0; y < heightArray.size(); y++){
            JSONArray widthArray = (JSONArray)heightArray.get(y);
            for(int x = 0; x < widthArray.size(); x++){
                JSONObject tr = (JSONObject)widthArray.get(x);
                System.out.println(tr.toString());
                img.setRGB(x, y, (new Color(((Long)tr.get("R")).intValue(),
                                            ((Long)tr.get("G")).intValue(),
                                            ((Long)tr.get("B")).intValue(),
                                            ((Long)tr.get("A")).intValue())).getRGB());
            }
            
        }

    }
    public myLayer(Dimension d){
        try {
            img = new BufferedImage((int)d.getWidth(), (int)d.getHeight(), TYPE_INT_ARGB);
            for (int i = 0; i < img.getWidth(); i++)
                for (int j = 0; j < img.getHeight(); j++) {
                    img.setRGB(i, j, (new Color(0, 0, 0, 0)).getRGB());
                }
        } catch (Exception e){System.out.println("ERROR");}

    }


    public void resize(Dimension d) {
        BufferedImage newImg = new BufferedImage(Math.max((int) d.getWidth(), img.getWidth()), Math.max((int) d.getHeight(), img.getHeight()), TYPE_INT_ARGB);
        for (int y = 0; y < newImg.getHeight(); y++)
            for (int x = 0; x < newImg.getWidth(); x++)
                try {
                    if (y < img.getHeight() && x < img.getWidth())
                        newImg.setRGB(x, y, img.getRGB(x, y));
                    else
                        newImg.setRGB(x, y, (new Color(0, 0, 0, 0)).getRGB());
                }catch (IndexOutOfBoundsException e) {
                    System.out.println(x + " " + y);
                }
        img = newImg;
    }



    public BufferedImage getImg(){
        return img;
    }

    public Dimension getMyDimensions(){
        return new Dimension(img.getWidth(),img.getHeight());
    }

    public void setActive(boolean b){
        isActive = b;
    }
    public boolean isActive(){
        return isActive;
    }

    public JSONObject getJSONObj() {
        JSONObject obj = new JSONObject();
        obj.put("active", isActive);

        JSONArray jaHeight = new JSONArray();
        for(int y = 0; y < img.getHeight(); y++){
            JSONArray jaWidth = new JSONArray();
            for(int x = 0; x < img.getWidth(); x++){
                Color color = new Color(img.getRGB(x,y), true);
                JSONObject pixel = new JSONObject();
                pixel.put("R", color.getRed());
                pixel.put("G", color.getGreen());
                pixel.put("B", color.getBlue());
                pixel.put("A", color.getAlpha());
                jaWidth.add(pixel);
            }
            jaHeight.add(jaWidth);
        }

        obj.put("matrix", jaHeight);

        return obj;
    }
}
