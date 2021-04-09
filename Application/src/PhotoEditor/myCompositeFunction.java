package PhotoEditor;


import netscape.javascript.JSObject;
import org.json.simple.*;

import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class myCompositeFunction {

    private String name;
    private JSONArray array;

    public myCompositeFunction(String name){
        this.name = name;
        array = new JSONArray();
    }

    public void add(String operation){
        JSONObject obj = new JSONObject();
        obj.put("type", operation);
        array.add(obj);
    }
    public void add(String operation, int arg){
        JSONObject obj = new JSONObject();
        obj.put("type", operation);
        obj.put("arg", arg);
        array.add(obj);
    }

    public void finish(){
        try {
            FileWriter fw = new FileWriter(name + ".fun");
            fw.write(array.toString());
            fw.close();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }


}
