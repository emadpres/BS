
/**
 * Title:        <p>
 * Description:  <p>
 * Copyright:    Copyright (c) <p>
 * Company:      <p>
 * @author
 * @version 1.0
 */


public class Test_Hopfield {
  static float [] data [] = {
    {1, 1, 1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, 1, 1, 1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, 1, 1, 1}
  };
  static Hopfield test;
  public static void main(String[] args) {
    test = new Hopfield(10);
    test.addTrainingData(data[0]);
    test.addTrainingData(data[1]);
    test.addTrainingData(data[2]);
    test.train();
    helper(test, "pattern 0", data[0]);
    helper(test, "pattern 1", data[1]);
    helper(test, "pattern 2", data[2]);
  }
  private static void helper(Hopfield test, String s, float [] test_data) {
    float [] dd = new float[10];
    for (int i=0; i<10; i++) {
      dd[i] = test_data[i];
    }
    int index = (int)(9.0f * (float)Math.random());
    if (dd[index] < 0.0f) dd[index] = 1.0f;
    else                  dd[index] = -1.0f;
    float [] rr = test.recall(dd, 5);
    System.out.println(s);
    for (int i=0; i<10; i++) System.out.print(pp(rr[i]) + " ");
    System.out.println();
  }
  private static int pp(float x) {
    if (x > 0.1f) return 1;
    return 0;
  }
}
