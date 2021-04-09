package PhotoEditor;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.border.EmptyBorder;
import javax.swing.border.TitledBorder;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Map;


public class PhotoEditor extends Frame {
    private myImage slika;

    private Button bAddNewLayer = new Button("Add new Layer");
    private Button bAddNewSelection = new Button("Start Creating New Selection");
    private Button bAddNewCompFun = new Button("Start Creating Composite Function");
    private Button bDoOperation = new Button("Do operation");

    private Checkbox typeOfNewLayer[] = new Checkbox[3];
    private TextField photoPath = new TextField();
    private TextField layerDimX = new TextField();
    private TextField layerDimY = new TextField();
    private List LayerList = new List(4,true);

    private TextField NewSelectionName = new TextField();
    private List SelectionList = new List(4, true);


    private Choice FunctionsList = new Choice();
    private TextField FunctionParametar = new TextField();
    private TextField NewCompFuncName = new TextField();
    private HashSet<String> FunctionsWithArguments = new HashSet<String>();
    private boolean makingCompositeFunction = false;
    private myCompositeFunction tempCompFunc;

    private Button bSaveProject = new Button("Save Project");
    private Button bSaveBMP = new Button("Save BMP Picture");
    private Button bSavePAM = new Button("Save PAM Picture");

    private Button bOpenOldProject = new Button("Open Old Project");
    ScrollPane sp = new ScrollPane();


    public PhotoEditor() {
        super("PhotoEditor");
        slika = new myImage();
        setSize(1500,800);

        sp.add(slika);
        add(sp, BorderLayout.CENTER);
        add(bottom(), BorderLayout.WEST);
        addListeners();
        basicFunctions();
        updateImage();
        setVisible(true);
        sp.repaint();
    }

    private void updateImage(){
        for(Map.Entry<String, mySelection> sel: slika.getMySelections().entrySet()){
            SelectionList.add(sel.getKey());
            if(sel.getValue().isActive())
                SelectionList.select(SelectionList.getItemCount()-1);
        }

        int i = 0;
        for(myLayer lay: slika.getMyLayers()){
            LayerList.add("" + i++);
            if(lay.isActive())
                LayerList.select(LayerList.getItemCount()-1);
        }

        for(String s: slika.getCompFunc())
            FunctionsList.add(s);
    }

    private void basicFunctions(){
        FunctionsList.add("Transparency");

        FunctionsList.add("Addition");
        FunctionsList.add("Subtraction");
        FunctionsList.add("rSubtraction");
        FunctionsList.add("Multiplication");
        FunctionsList.add("Division");
        FunctionsList.add("rDivision");

        FunctionsList.add("Absolute");
        FunctionsList.add("Logarithm");
        FunctionsList.add("Maximum");
        FunctionsList.add("Minimum");
        FunctionsList.add("Power");

        FunctionsList.add("Mediana");
        FunctionsList.add("Inversion");
        FunctionsList.add("Gray");
        FunctionsList.add("BlackWhite");

        FunctionsWithArguments.add("Transparency");
        FunctionsWithArguments.add("Addition");
        FunctionsWithArguments.add("Subtraction");
        FunctionsWithArguments.add("rSubtraction");
        FunctionsWithArguments.add("Multiplication");
        FunctionsWithArguments.add("Division");
        FunctionsWithArguments.add("rDivision");
        FunctionsWithArguments.add("Maximum");
        FunctionsWithArguments.add("Minimum");
        FunctionsWithArguments.add("Power");
    }

    private Panel bottom() {
        //Panel p = new Panel(new GridLayout(3,1));
        Panel p = new Panel();
        p.setLayout(new BoxLayout(p, BoxLayout.Y_AXIS));
        //Panel p = new Panel();

        //p.setBounds(0, 0, 200, 1000);

        JPanel pAddLayer = new JPanel();
        pAddLayer.setLayout(new BoxLayout(pAddLayer, BoxLayout.Y_AXIS));
        pAddLayer.setBackground(new Color(130,220,240));
        bAddNewLayer.setBackground(new Color(220,220,220));
        Panel pGroup = new Panel();
        CheckboxGroup grupa = new CheckboxGroup();
        typeOfNewLayer[0] = new Checkbox("empty", grupa, true);
        typeOfNewLayer[1] = new Checkbox("empty with dimensions", grupa, false);
        typeOfNewLayer[2] = new Checkbox("picture", grupa, false);
        pGroup.add(typeOfNewLayer[0]);
        pGroup.add(typeOfNewLayer[1]);
        pGroup.add(typeOfNewLayer[2]);
        pAddLayer.add(pGroup);
        Panel tf = new Panel();
        tf.add(layerDimX);
        tf.add(layerDimY);
        pAddLayer.add(tf);
        pAddLayer.add(photoPath);
        pAddLayer.add(bAddNewLayer);
        pAddLayer.add(LayerList);
        TitledBorder tbL = new TitledBorder("LAYERS");
        tbL.setTitleJustification(TitledBorder.CENTER);
        pAddLayer.setBorder(tbL);
        p.add(pAddLayer);



        JPanel pAddSelection = new JPanel();
        pAddSelection.setLayout(new BoxLayout(pAddSelection, BoxLayout.Y_AXIS));
        pAddSelection.setBackground(new Color(250,250,85));

        NewSelectionName.setSize(100, 5);
        pAddSelection.add(NewSelectionName);
        pAddSelection.add(bAddNewSelection);
        bAddNewSelection.setBackground(new Color(220, 220, 220));

        JPanel ph = new JPanel(new GridLayout(1,1));
        ph.add(SelectionList);
        ph.setBorder(new EmptyBorder(5, 5, 5, 5));
        pAddSelection.add(ph);
        TitledBorder tbS = new TitledBorder("SELECTIONS");
        tbS.setTitleJustification(TitledBorder.CENTER);
        pAddSelection.setBorder(tbS);
        p.add(pAddSelection);




        JPanel pAddCompFunc = new JPanel(new GridLayout(3,1));
        pAddCompFunc.setBackground(new Color(210, 110, 255));
        TitledBorder tbF = new TitledBorder("FUNCTIONS");
        tbF.setTitleJustification(TitledBorder.CENTER);
        pAddCompFunc.setBorder(tbF);

        Panel doFunction = new Panel();
        doFunction.add(FunctionsList);
        doFunction.add(FunctionParametar);
        doFunction.add(bDoOperation);
        pAddCompFunc.add(doFunction);


        pAddCompFunc.add(NewCompFuncName);
        pAddCompFunc.add(bAddNewCompFun);
        p.add(pAddCompFunc);

        JPanel pExport = new JPanel();
        pExport.setBackground(new Color(110,250,60));
        TitledBorder tbE = new TitledBorder("EXPORT");
        tbE.setTitleJustification(TitledBorder.CENTER);
        pExport.setBorder(tbE);
        pExport.add(bSaveBMP);
        pExport.add(bSavePAM);
        pExport.add(bSaveProject);

        p.add(pExport);
        p.add(bOpenOldProject);

        Panel pOmot = new Panel();
        pOmot.add(p, BorderLayout.NORTH);
        return pOmot;
    }

    private void addListeners() {
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                dispose();
            }
        });


        selectionListeners();
        layerListeners();
        functionsListeners();
        exportListeners();

        bSaveProject.addActionListener(e->slika.saveProject());

    }

    private void selectionListeners(){
        bAddNewSelection.addActionListener(e->{
            slika.CreatingNewSelection(NewSelectionName.getText());
            if(slika.isCreatingNewSelection()){
                bAddNewSelection.setLabel("Finish Creating Selection");
                NewSelectionName.setEnabled(false);
            }
            else {
                bAddNewSelection.setLabel("Start Creating New Selection");
                SelectionList.add(NewSelectionName.getText());
                SelectionList.select(SelectionList.getItemCount()-1);
                NewSelectionName.setText("");
                NewSelectionName.setEnabled(true);
                slika.repaint();
            }
        });

        SelectionList.addItemListener(e -> {
            ArrayList<String> al = new ArrayList();
            for(String n:SelectionList.getSelectedItems())
                al.add(n);
            for(String names: SelectionList.getItems())
                    slika.setSelectionState(names, al.contains(names));
            slika.repaint();

        });


    }

    private void layerListeners(){
        bAddNewLayer.addActionListener(e->{
            int b = -1;
            if(typeOfNewLayer[0].getState())
                b = slika.CreatingNewLayer();
            if(typeOfNewLayer[1].getState())
                b = slika.CreatingNewLayer(new Dimension(Integer.parseInt(layerDimX.getText()), Integer.parseInt(layerDimY.getText())));
            if(typeOfNewLayer[2].getState())
                b = slika.CreatingNewLayer(photoPath.getText());
            if(b > -1) {
                LayerList.add("" + b);
                LayerList.select(LayerList.getItemCount()-1);
            }
            slika.repaint();
        });

        LayerList.addItemListener(e -> {
            ArrayList<String> al = new ArrayList();
            for(String n:LayerList.getSelectedItems())
                al.add(n);
            for(String names: LayerList.getItems())
                slika.setLayerState(Integer.valueOf(names), al.contains(names));
            slika.updatingImage();
            slika.repaint();

        });

    }

    private void functionsListeners(){

        FunctionsList.addItemListener(e->{
            if(FunctionsWithArguments.contains(e.getItem().toString()))
                FunctionParametar.setEnabled(true);
            else
                FunctionParametar.setEnabled(false);
        });

        bDoOperation.addActionListener(e->{
            try {
                String operation = FunctionsList.getSelectedItem();
                if (makingCompositeFunction) {
                    if (FunctionsWithArguments.contains(operation))
                        tempCompFunc.add(operation, Integer.parseInt(FunctionParametar.getText()));
                    else
                        tempCompFunc.add(operation);
                } else {
                    if (FunctionsWithArguments.contains(operation))
                        operation += " " + FunctionParametar.getText();
                    doOperation(operation);
                }
            }catch (NumberFormatException nfe){ }
        });

        bAddNewCompFun.addActionListener(e->{
            if(!makingCompositeFunction) {
                makingCompositeFunction = true;
                bDoOperation.setLabel("Add");
                bAddNewCompFun.setLabel("Finish Creating Composite Function");
                tempCompFunc = new myCompositeFunction(NewCompFuncName.getText());
                slika.addCompositeFunction(NewCompFuncName.getText());
                NewCompFuncName.setText("");
                NewCompFuncName.setEnabled(false);
            }
            else{
                makingCompositeFunction = false;
                bDoOperation.setLabel("Do operation");
                bAddNewCompFun.setLabel("Start Creating Composite Function");
                NewCompFuncName.setEnabled(true);
                tempCompFunc.finish();
                tempCompFunc = null;
            }
        });
    }

    public void doOperation(String operation) {
        try {
            slika.saveProject();
            String file = "POOP_exe.exe" + " " + operation;
            Runtime runtime = Runtime.getRuntime();
            Process process = runtime.exec(file);
            System.out.println("waiting to finish");
            process.waitFor();
            System.out.println("finished");
            slika = new myImage("myProject.json");
            slika.updatingImage();
            sp.removeAll();
            slika.repaint();
            sp.add(slika);
            sp.repaint();
            repaint();

        }catch (IllegalArgumentException | IOException | InterruptedException e){}


    }

    private void exportListeners(){
        bSaveBMP.addActionListener(e->{
            System.out.println("Pokusavam da sacuvam");
            slika.exportToBMP();

        });

        bSavePAM.addActionListener(e->{
            slika.exportToPAM();
        });

        bOpenOldProject.addActionListener(e -> {
            slika.fromJson("myProject.json");
            updateImage();
            repaint();
        });

    }

    public static void main(String[] args) {
        new PhotoEditor();
    }
}
