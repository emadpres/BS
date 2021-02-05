
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
/**
 * Title:        <p>
 * Description:  <p>
 * Copyright:    Copyright (c) <p>
 * Company:      <p>
 * @author
 * @version 1.0
 */

public class GUITest_1H extends JFrame {
  static float [] in1 = { -0.4f, -0.4f, +0.4f };
  static float [] in2 = { -0.4f, +0.4f, -0.4f };
  static float [] in3 = { +0.4f, -0.4f, -0.4f };

  static float [] out1= { +0.4f, -0.4f, -0.4f};
  static float [] out2= { -0.4f, -0.4f, +0.4f};
  static float [] out3= { -0.4f, +0.4f, -0.4f};

  static float [] test1 = { -0.2f, -0.45f, +0.35f };
  static float [] test2 = { -0.33f, +0.41f, -0.38f };
  static float [] test3 = { +0.33f, -0.41f, -0.23f };

  Neural_1H nn = new Neural_1H(3, 3, 3);
  Plot1DPanel inputPanel = new Plot1DPanel(3, -1.0f, 1.0f, nn.inputs);
  Plot1DPanel hiddenPanel = new Plot1DPanel(3, -4.0f, 4.0f, nn.hidden);
  Plot1DPanel outputPanel = new Plot1DPanel(3, -1.0f, 1.0f, nn.outputs);
  Plot2DPanel w1Panel = new Plot2DPanel(3, 3, -1.0f, 1.0f, nn.W1);
  Plot2DPanel w2Panel = new Plot2DPanel(3, 3, -4.0f, 4.0f, nn.W2);
  JButton jButton1 = new JButton();
  JLabel jLabel1 = new JLabel();
  JLabel jLabel2 = new JLabel();
  JLabel jLabel3 = new JLabel();
  JLabel jLabel4 = new JLabel();
  JLabel jLabel5 = new JLabel();

  public GUITest_1H() {
    try {
    nn.addTrainingExample(in1, out1);
    nn.addTrainingExample(in2, out2);
    nn.addTrainingExample(in3, out3);
      jbInit();
      this.setSize(450, 350);
      this.setVisible(true);
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    GUITest_1H GUITest_1H1 = new GUITest_1H();
  }

  private void jbInit() throws Exception {
    this.getContentPane().setLayout(null);
    inputPanel.setBounds(new Rectangle(5, 30, 400, 20));
    hiddenPanel.setBounds(new Rectangle(5, 138, 400, 20));
    outputPanel.setBounds(new Rectangle(5, 240, 400, 20));
    w1Panel.setBounds(new Rectangle(200, 50, 60, 60));
    w2Panel.setBounds(new Rectangle(200, 158, 60, 60));
    jButton1.setText("Rest and Run");
    jButton1.setBounds(new Rectangle(246, 290, 148, 28));
    jButton1.addMouseListener(new java.awt.event.MouseAdapter() {

      public void mousePressed(MouseEvent e) {
        do_run_button(e);
      }
    });
    this.setDefaultCloseOperation(3);
    jLabel1.setText("Input neurons:");
    jLabel1.setBounds(new Rectangle(4, 3, 144, 19));
    jLabel2.setText("Hidden neurons:");
    jLabel2.setBounds(new Rectangle(4, 102, 144, 19));
    jLabel3.setText("Output neurons:");
    jLabel3.setBounds(new Rectangle(4, 208, 240, 19));
    jLabel4.setText("input to hidden weights");
    jLabel4.setBounds(new Rectangle(270, 80, 150, 19));
    jLabel5.setText("hidden to output weights");
    jLabel5.setBounds(new Rectangle(270, 180, 150, 19));
    this.getContentPane().add(inputPanel, null);
    this.getContentPane().add(hiddenPanel, null);
    this.getContentPane().add(outputPanel, null);
    this.getContentPane().add(w1Panel, null);
    this.getContentPane().add(w2Panel, null);
    this.getContentPane().add(jButton1, null);
    this.getContentPane().add(jLabel1, null);
    this.getContentPane().add(jLabel2, null);
    this.getContentPane().add(jLabel3, null);
    this.getContentPane().add(jLabel4, null);
    this.getContentPane().add(jLabel5, null);
  }

  void do_run_button(MouseEvent e) {
    Graphics g1 = inputPanel.getGraphics();
    Graphics g2 = hiddenPanel.getGraphics();
    Graphics g3 = outputPanel.getGraphics();
    Graphics g4 = w1Panel.getGraphics();
    Graphics g5 = w2Panel.getGraphics();
    for (int i=0; i<600; i++) {
      float error = nn.train();
     //if ((i + 19) % 20 == 0) System.out.println("cycle " + i + " error is " + error);
      inputPanel.paint(g1);
      hiddenPanel.paint(g2);
      outputPanel.paint(g3);
      w1Panel.paint(g4);
      w2Panel.paint(g5);
      if (i > 580) {
         try { Thread.sleep(500L); } catch (Exception e9) { }
      } else {
         try { Thread.sleep(30L); } catch (Exception e9) { }
      }
    }

  }
}
