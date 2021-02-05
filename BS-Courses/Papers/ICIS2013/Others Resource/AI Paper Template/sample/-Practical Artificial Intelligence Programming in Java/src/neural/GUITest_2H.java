/**
 * Title:        <p>
 * Description:  <p>
 * Copyright:    Copyright (c) <p>
 * Company:      <p>
 * @author
 * @version 1.0
 */

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class GUITest_2H extends JFrame {
  static float [] in1 = { -0.4f, -0.4f, +0.4f };
  static float [] in2 = { -0.4f, +0.4f, -0.4f };
  static float [] in3 = { +0.4f, -0.4f, -0.4f };

  static float [] out1= { +0.4f, -0.4f, -0.4f};
  static float [] out2= { -0.4f, -0.4f, +0.4f};
  static float [] out3= { -0.4f, +0.4f, -0.4f};

  static float [] test1 = { -0.2f, -0.45f, +0.35f };
  static float [] test2 = { -0.33f, +0.41f, -0.38f };
  static float [] test3 = { +0.33f, -0.41f, -0.23f };

  Neural_2H nn = new Neural_2H(3, 3, 3, 3);
  Plot1DPanel inputPanel = new Plot1DPanel(3, -1.0f, 1.0f, nn.inputs);
  Plot1DPanel hidden1Panel = new Plot1DPanel(3, -1.0f, 1.0f, nn.hidden1);
  Plot1DPanel hidden2Panel = new Plot1DPanel(3, -1.0f, 1.0f, nn.hidden2);
  Plot1DPanel outputPanel = new Plot1DPanel(3, -1.0f, 1.0f, nn.outputs);
  Plot2DPanel w1Panel = new Plot2DPanel(3, 3, -1.0f, 1.0f, nn.W1);
  Plot2DPanel w2Panel = new Plot2DPanel(3, 3, -1.0f, 1.0f, nn.W2);
  Plot2DPanel w3Panel = new Plot2DPanel(3, 3, -1.0f, 1.0f, nn.W3);
  JButton jButton1 = new JButton();
  JLabel jLabel1 = new JLabel();
  JLabel jLabel2 = new JLabel();
  JLabel jLabel2b = new JLabel();
  JLabel jLabel3 = new JLabel();
  JLabel jLabel4 = new JLabel();
  JLabel jLabel4b = new JLabel();
  JLabel jLabel5 = new JLabel();

  public GUITest_2H() {
    try {
    nn.addTrainingExample(in1, out1);
    nn.addTrainingExample(in2, out2);
    nn.addTrainingExample(in3, out3);
      jbInit();
      this.setSize(450, 450);
      this.setVisible(true);
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    GUITest_2H GUITest_1H1 = new GUITest_2H();
  }

  private void jbInit() throws Exception {
    this.getContentPane().setLayout(null);
    inputPanel.setBounds(new Rectangle(5, 30, 400, 20));
    hidden1Panel.setBounds(new Rectangle(5, 138, 400, 20));
    hidden2Panel.setBounds(new Rectangle(5, 238, 400, 20));
    outputPanel.setBounds(new Rectangle(5, 340, 400, 20));
    w1Panel.setBounds(new Rectangle(160, 50, 60, 60));
    w2Panel.setBounds(new Rectangle(160, 158, 60, 60));
    w3Panel.setBounds(new Rectangle(160, 258, 60, 60));
    jButton1.setText("Rest and Run");
    jButton1.setBounds(new Rectangle(246, 380, 148, 28));
    jButton1.addMouseListener(new java.awt.event.MouseAdapter() {

      public void mousePressed(MouseEvent e) {
        do_run_button(e);
      }
    });
    this.setDefaultCloseOperation(3);
    jLabel1.setText("Input neurons:");
    jLabel1.setBounds(new Rectangle(4, 3, 144, 19));
    jLabel2.setText("Hidden 1 neurons:");
    jLabel2.setBounds(new Rectangle(4, 102, 144, 19));
    jLabel2b.setText("Hidden 2 neurons:");
    jLabel2b.setBounds(new Rectangle(4, 202, 144, 19));
    jLabel3.setText("Output neurons:");
    jLabel3.setBounds(new Rectangle(4, 308, 240, 19));
    jLabel4.setText("input to hidden 1 weights");
    jLabel4.setBounds(new Rectangle(230, 80, 170, 19));
    jLabel4b.setText("hidden 1 to hidden 2 weights");
    jLabel4b.setBounds(new Rectangle(230, 180, 170, 19));
    jLabel5.setText("hidden 2 to output weights");
    jLabel5.setBounds(new Rectangle(230, 280, 170, 19));
    this.getContentPane().add(inputPanel, null);
    this.getContentPane().add(hidden1Panel, null);
    this.getContentPane().add(hidden2Panel, null);
    this.getContentPane().add(outputPanel, null);
    this.getContentPane().add(w1Panel, null);
    this.getContentPane().add(w2Panel, null);
    this.getContentPane().add(w3Panel, null);
    this.getContentPane().add(jButton1, null);
    this.getContentPane().add(jLabel1, null);
    this.getContentPane().add(jLabel2, null);
    this.getContentPane().add(jLabel2b, null);
    this.getContentPane().add(jLabel3, null);
    this.getContentPane().add(jLabel4, null);
    this.getContentPane().add(jLabel4b, null);
    this.getContentPane().add(jLabel5, null);
  }

  void do_run_button(MouseEvent e) {
    Graphics g1 = inputPanel.getGraphics();
    Graphics g2 = hidden1Panel.getGraphics();
    Graphics g3 = hidden2Panel.getGraphics();
    Graphics g4 = outputPanel.getGraphics();
    Graphics g5 = w1Panel.getGraphics();
    Graphics g6 = w2Panel.getGraphics();
    Graphics g7 = w3Panel.getGraphics();
    for (int i=0; i<5600; i++) {
      float error = nn.train();
     //if ((i + 19) % 20 == 0) System.out.println("cycle " + i + " error is " + error);
      inputPanel.paint(g1);
      hidden1Panel.paint(g2);
      hidden2Panel.paint(g3);
      outputPanel.paint(g4);
      w1Panel.paint(g5);
      w2Panel.paint(g6);
      w3Panel.paint(g7);
      if (i > 5580) {
         try { Thread.sleep(300L); } catch (Exception e9) { }
      } else {
         try { Thread.sleep(10L); } catch (Exception e9) { }
      }
    }

  }
}
