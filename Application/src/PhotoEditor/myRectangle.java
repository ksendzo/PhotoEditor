package PhotoEditor;

import netscape.javascript.JSObject;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.JSONObject.*;

import java.awt.*;
import java.awt.geom.Rectangle2D;

public class myRectangle {
    private int x, y, h, w;

    public myRectangle(int x, int y, int w, int h){
        this.x = x;
        this.y = y;
        this.h = h;
        this.w = w;
    }
    public myRectangle(JSONObject jsonObject){
        System.out.println(jsonObject.toString());
        JSONArray ja = (JSONArray)jsonObject.get("coor");
        System.out.println(ja);
        this.x = ((Long) ja.get(1)).intValue();
        this.y = ((Long)ja.get(0)).intValue();

        JSONArray jad = (JSONArray)jsonObject.get("dim");
        this.h = ((Long)jad.get(0)).intValue();
        this.w = ((Long) jad.get(1)).intValue();
    }

    public void paint(Graphics og){
        og.setColor(Color.black);

        Graphics2D g = (Graphics2D)og;
        Rectangle2D rect = new Rectangle2D.Float( x, y, w, h );
        float[] dash = { 5F, 5F };
        Stroke dashedStroke = new BasicStroke( 2F, BasicStroke.CAP_SQUARE,
                BasicStroke.JOIN_MITER, 3F, dash, 0F );
        g.fill( dashedStroke.createStrokedShape( rect ) );
    }

    public JSONObject getJSONObj() {
        JSONObject obj = new JSONObject();

        JSONArray coor = new JSONArray();
        coor.add(y);
        coor.add(x);
        obj.put("coor", coor);

        JSONArray dim = new JSONArray();
        dim.add(h);
        dim.add(w);
        obj.put("dim", dim);

        return obj;
    }
}
