package PhotoEditor;

import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.nio.channels.SelectableChannel;
import java.util.*;
import javax.imageio.*;
import java.io.*;

import org.json.simple.*;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class myImage extends Canvas {
    private BufferedImage img;

    private ArrayList<myLayer> myLayers = new ArrayList<myLayer>();
    private HashMap<String, mySelection> mySelections = new HashMap<String, mySelection>();
    private ArrayList<String> myCompositeFunctions = new ArrayList<String>();

    private boolean isNewSelection = false;
    private mySelection newSelection = null;
    private int selX, selY;

    private myRectangle tempRec = null;

    public myImage(String path){
        fromJson(path);
        addListeners();
    }

    public myImage(){
        addListeners();
    }

    private void addListeners(){
        addMouseListener(new MouseAdapter(){
            public void mousePressed(MouseEvent e){
                if(isNewSelection){
                    selX = e.getX();
                    selY = e.getY();
                }
            }
            public void mouseReleased(MouseEvent e){
                if(isNewSelection) {
                    newSelection.addRect(tempRec);
                    tempRec = null;
                    repaint();
                }
            }
        });

        this.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                if(isNewSelection) {
                    tempRec = new myRectangle(Math.min(selX, e.getX()), Math.min(selY, e.getY()), Math.abs(selX-e.getX()), Math.abs(selY-e.getY()));
                    repaint();
                }
            }
        });
    }

    public void CreatingNewSelection(String name){
        if(!isNewSelection) {
            newSelection = new mySelection(name);
            mySelections.put(newSelection.getName(), newSelection);
            isNewSelection = true;
        }
        else {
            isNewSelection = false;
            newSelection = null;
        }
    }

    public int CreatingNewLayer(){
        if(img == null) return - 1;
        return CreatingNewLayer(new Dimension(img.getWidth(), img.getHeight()));
    }
    public int CreatingNewLayer(Dimension d){
        myLayers.add(new myLayer(d));
        updatingImage();
        return myLayers.size() - 1;
    }
    public int CreatingNewLayer(String path){
        myLayers.add(new myLayer(path));
        updatingImage();
        return myLayers.size() - 1;
    }

    public void updatingImage(){
        if(img != null) {
            myLayer lastLayer = myLayers.get(myLayers.size()-1);
            lastLayer.resize(new Dimension(img.getWidth(), img.getHeight())); // prosiruje nov ako je potrebno
            myLayers.forEach(l->l.resize(lastLayer.getMyDimensions())); // prosiruje stare slojeve prema novom ako je potrebno
        }
        setImgValue();
    }


    private void setImgValue(){
        if(myLayers.isEmpty())
            return;
        img = new BufferedImage((int)myLayers.get(0).getMyDimensions().getWidth(), (int)myLayers.get(0).getMyDimensions().getHeight(), BufferedImage.TYPE_INT_ARGB);
        for(int x = 0; x < img.getWidth(); x++)
            for(int y = 0; y < img.getHeight(); y++)
                setPixelValue(x, y);
    }
    private void setPixelValue(int x, int y){

        int r = 0, b = 0, g = 0, a = 0;
        int ostatak = 255;
        for(myLayer l: myLayers){
            if(!l.isActive())
                continue;
            Color col = new Color(l.getImg().getRGB(x,y), true);
            r += col.getRed() * ostatak * col.getAlpha() / 255 / 255;
            g += col.getGreen() * ostatak * col.getAlpha() / 255 / 255;
            b += col.getBlue() * ostatak * col.getAlpha() / 255 / 255;
            a += col.getAlpha() * ostatak / 255;
            if(r > 255) r = 255; // ne bi trebalo ikada da prekoraci
            if(g > 255) g = 255;
            if(b > 255) b = 255;
            if(a > 255) a = 255;
            if(r < 0) r = 0;
            if(g < 0) g = 0;
            if(b < 0) b = 0;
            if(a < 0) a = 0;
            ostatak -= ostatak * col.getAlpha() / 255;
        }

        img.setRGB(x, y, (new Color(r,g,b,a)).getRGB());

    }


    public HashMap<String, mySelection> getMySelections(){
        return mySelections;
    }


    public boolean isCreatingNewSelection() {return isNewSelection; }


    public void saveProject() {
        try {
            //File f = new File("myProject.json");
            //FileWriter fw = new FileWriter("myProject.json");"C:\\Users\\Ksendzo\\IdeaProjects\\POOP_PhotoEditor\\src\\PhotoEditor.PhotoEditor\\"
            FileWriter fw = new FileWriter("myProject.json");

            JSONObject obj = new JSONObject();

            obj.put("dimensions", getJSONDimensions());
            obj.put("layers", getJSONLayers());
            obj.put("selections", getJSONSelections());
            obj.put("cfPaths", getJSONCompFun());

            fw.write(obj.toString());
            fw.close();
        } catch (IOException e){}

    }

    private JSONArray getJSONCompFun() {
        JSONArray ar = new JSONArray();
        for(String s: myCompositeFunctions)
            ar.add(s);
        return ar;
    }

    private JSONObject getJSONSelections() {
        JSONObject obj = new JSONObject();

        for(Map.Entry<String, mySelection> sel: mySelections.entrySet()){
            obj.put(sel.getKey(), sel.getValue().getJOSNObj());
        }

        return obj;
    }

    private JSONArray getJSONLayers() {
        JSONArray jsonArray = new JSONArray();
        for(myLayer ml: myLayers)
            jsonArray.add(ml.getJSONObj());
        return jsonArray;
    }

    private JSONArray getJSONDimensions() {
        JSONArray obj = new JSONArray();
        obj.add(img.getWidth());
        obj.add(img.getHeight());
        return obj;
    }


    public void fromJson(String path){
        JSONParser jsonParser = new JSONParser();
        try{
            Object obj = jsonParser.parse(new FileReader(path));
            JSONObject jsonObject = (JSONObject) obj;

            JSONArray cfPaths = (JSONArray) jsonObject.get("cfPaths");
            Iterator<String> iterator = cfPaths.iterator();
            while (iterator.hasNext())
                myCompositeFunctions.add(iterator.next());

            JSONArray layers = (JSONArray) jsonObject.get("layers");
            Iterator<JSONObject> layersIterator = layers.iterator();
            while(layersIterator.hasNext()){
                myLayers.add(new myLayer(layersIterator.next()));
                updatingImage();
            }


            Map selections = (Map) jsonObject.get("selections");
            if(selections.toString().equals("{}")){
                System.out.println("nema selekcije(a)");
            }
            Iterator<Map.Entry> selectionsIterator = selections.entrySet().iterator();
            while(selectionsIterator.hasNext()){
                Map.Entry nSel = selectionsIterator.next();
                mySelection newSelection = new mySelection((JSONObject)nSel.getValue());
                mySelections.put(newSelection.getName(), newSelection);
            }



            setImgValue();

            //System.out.println("Name is: " + name);

        } catch (ParseException e) {
            e.printStackTrace();
        } catch (FileNotFoundException e) {}
        catch (IOException e) {
            e.printStackTrace();
        }

    }


    @Override
    public void paint(Graphics g) {
        g.drawImage(img, 0, 0, null);
        mySelections.forEach((name, sel) -> sel.paint(g));
        if(tempRec != null)
            tempRec.paint(g);
    }

    public void setSelectionState(String name, boolean active) {
        mySelections.get(name).setActive(active);
    }

    public ArrayList<myLayer> getMyLayers() {
        return myLayers;
    }

    public void setLayerState(int index, boolean active) {
        myLayers.get(index).setActive(active);

    }

    public void addCompositeFunction(String text) {
        myCompositeFunctions.add(text);
    }

    public ArrayList<String> getCompFunc() {
        return myCompositeFunctions;
    }


    public void exportToBMP(){
        try {
            File file = new File("saved.bmp");
            ImageIO.write(img, "bmp", file);
            System.out.println("sacuvano");
            System.out.println(file.getAbsolutePath());
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void exportToPAM(){
        try {
            File fw = new File("slika.pam");
            FileOutputStream fos = new FileOutputStream(fw);

            StringBuilder sb = new StringBuilder();

            String sp = "\n";
            sb.append("P7").append(sp).append("WIDTH ")
                    .append("" + img.getWidth()).append(sp)
                    .append("HEIGHT ")
                    .append("" + img.getHeight()).append(sp)
                    .append("DEPTH 4").append(sp)
                    .append("MAXVAL 255").append(sp)
                    .append("TUPLTYPE RGB_ALPHA").append(sp)
                    .append("ENDHDR").append(sp);
            String str = sb.toString();
            byte[] niz = new byte[str.length()];
            for(int i = 0; i < str.length();i++)
                niz[i] = (byte)str.charAt(i);
            fos.write(niz);

            //fw.write(sb.toString());
            for(int y = 0; y < img.getHeight(); y++){
                for(int x = 0; x < img.getWidth(); x++){
                    Color c = new Color(img.getRGB(x, y), true);
                    byte b = (byte)c.getRed();
                    fos.write(b);
                    fos.write((byte) c.getGreen());
                    fos.write((byte)c.getBlue());
                    fos.write((byte)c.getAlpha());
                }
                //fos.write((byte)(10));
            }



        } catch (IOException e) {
            e.printStackTrace();
        }


    }

}
