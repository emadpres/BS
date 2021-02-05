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

public class GraphPanel extends java.awt.Canvas { // JPanel {

  public GraphPanel(float [] data) {
    super();
    this.data = data;
  }
  Color black = new Color(0, 0, 0);
  float [] data;
  public void paint(Graphics g) {
    if (data == null) return;
    int width = this.getWidth();
    int height = this.getHeight();
    System.out.println("height="+height);
    float min = 99999999.9f;
    float max = -min;
    int maxindex = 0;
    float maxval = 0.0f;
    for (int i=0; i<data.length; i++) {
      if (min > data[i]) min = data[i];
      if (max < data[i]) {
        max = data[i];
        maxindex = i;
        maxval = max;
      }
    }
    System.out.println("min=" + min +", max=" + max +
                       ", max index="+maxindex + ", max val="+maxval);
    g.setColor(black);
    for (int i=0; i<data.length - 1; i++) {
      float y1 = height - 5 - 0.95f *height * ((data[i] - min)  / (max - min));
      float y2 = height - 5 - 0.95f *height * ((data[i+1] - min)  / (max - min));
      //System.out.println("data["+i+"]="+data[i]+", y1="+y1+", y2="+y2);
      g.drawLine(i+20, (int)y1, i+21, (int)y2);
    }
    float yzero = height - 5 - 0.95f *height * ((0.0f - min)  / (max - min));
    g.drawLine(20, (int)yzero, data.length + 19, (int)yzero);
  }
}
