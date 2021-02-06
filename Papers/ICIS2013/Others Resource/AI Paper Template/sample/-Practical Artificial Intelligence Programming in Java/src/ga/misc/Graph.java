
import javax.swing.*;
import java.awt.*;
/**
 * Title:        Graph<p>
 * Description:  Simple program to produce a graph for the book<p>
 * Copyright:    Copyright (c) Mark Watson<p>
 * Company:      <p>
 * @author Mark Watson
 * @version 1.0
 */


public class Graph extends JFrame {
  GraphPanel jPanel1;
  float [] data;
  public Graph() {
    try {
      int size = 500;
      data = new float[size];
      float xmin = 0;
      float xmax = 10;
      for (int i=0; i<size; i++) {
        float x = i;
        x = xmin + x * (xmax - xmin) / (float)size;
        if (i==190) System.out.println("x="+x);
        float x1 = (float)Math.sin(x);
        float x2 = (float)Math.sin(x * 0.4f);
        float x3 = (float)Math.sin(x * 3.0f);
        data[i] = x1 * x2 * x3;
      }
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  public static void main(String[] args) {
    Graph untitled11 = new Graph();
  }

  private void jbInit() throws Exception {
    jPanel1 = new GraphPanel(data);
    jPanel1.setBackground(Color.white);
    this.setDefaultCloseOperation(3);
    this.getContentPane().add(jPanel1, BorderLayout.CENTER);
    setSize(550, 500);
    jPanel1.setVisible(true);
    setVisible(true);
  }
}