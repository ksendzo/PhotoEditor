package PhotoEditor;

import java.awt.*;
import java.util.ArrayList;
import java.util.Iterator;
import org.json.simple.*;


public class mySelection {
    private ArrayList<myRectangle> myRectangles = new ArrayList<myRectangle>();
    private boolean isActive = true;
    private String name;

    public mySelection(String name){
        this.name = name;
    }
    public mySelection(JSONObject jsonObject){
        isActive = (boolean)jsonObject.get("active");
        name = (String)jsonObject.get("name");

        JSONArray rects = (JSONArray)jsonObject.get("rects");
        Iterator rectsIterator = rects.iterator();
        while(rectsIterator.hasNext()){
            myRectangles.add(new myRectangle((JSONObject)rectsIterator.next()));
        }
    }


    public void addRect(myRectangle r){
        myRectangles.add(r);
    }


    public boolean isActive(){
        return isActive;
    }
    public void setActive(boolean b){
        isActive = b;
    }


    public String getName(){
        return name;
    }


    public void paint(Graphics g) {
        if (isActive){
            myRectangles.stream().forEach((rectTemp) -> rectTemp.paint(g));
        }
    }

    public JSONObject getJOSNObj() {
        JSONObject obj = new JSONObject();

        obj.put("name", name);
        obj.put("active", isActive);

        JSONArray ar = new JSONArray();
        for(myRectangle rec: myRectangles)
            ar.add(rec.getJSONObj());
        obj.put("rects", ar);

        return obj;
    }
}
