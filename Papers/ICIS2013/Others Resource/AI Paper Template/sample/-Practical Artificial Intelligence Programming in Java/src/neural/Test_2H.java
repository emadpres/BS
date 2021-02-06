/**
 * Title:        <p>
 * Description:  <p>
 * Copyright:    Copyright (c) <p>
 * Company:      <p>
 * @author
 * @version 1.0
 */


public class Test_2H {

  static float [] in1 = { -0.4f, -0.4f, +0.4f };
  static float [] in2 = { -0.4f, +0.4f, -0.4f };
  static float [] in3 = { +0.4f, -0.4f, -0.4f };

  static float [] out1= { +0.4f, -0.4f, -0.4f};
  static float [] out2= { -0.4f, -0.4f, +0.4f};
  static float [] out3= { -0.4f, +0.4f, -0.4f};

  static float [] test1 = { -0.2f, -0.45f, +0.35f };
  static float [] test2 = { -0.33f, +0.41f, -0.38f };
  static float [] test3 = { +0.33f, -0.41f, -0.23f };

  public static void main(String[] args) {
    Neural_2H nn = new Neural_2H(3, 3, 3, 3);
    nn.addTrainingExample(in1, out1);
    nn.addTrainingExample(in2, out2);
    nn.addTrainingExample(in3, out3);
    for (int i=0; i<2002; i++) {
      float error = nn.train();
      if ((i + 99) % 100 == 0) System.out.println("cycle " + i + " error is " + error);
    }
    test_recall(nn, test1);
    test_recall(nn, test2);
    test_recall(nn, test3);

    nn.save("test.neural");
    Neural_2H nn2 = Neural_2H.Factory("test.neural");
    nn2.addTrainingExample(in1, out1);
    nn2.addTrainingExample(in2, out2);
    nn2.addTrainingExample(in3, out3);
    for (int i=0; i<102; i++) {
      float error = nn2.train();
      if ((i + 19) % 20 == 0) System.out.println("cycle " + i + " error is " + error);
    }
    test_recall(nn2, test1);
    test_recall(nn2, test2);
    test_recall(nn2, test3);
  }
  public static void test_recall(Neural_2H nn, float [] inputs) {
    float [] results = nn.recall(inputs);
    System.out.print("Test case: ");
    for (int i=0; i<inputs.length; i++) System.out.print(pp(inputs[i]) + " ");
    System.out.print(" results: ");
    for (int i=0; i<results.length; i++) System.out.print(pp(results[i]) + " ");
    System.out.println();
  }
  public static String pp(float x) {
    String s = new String("" + x + "00");
    int index = s.indexOf(".");
    if (index > -1) s = s.substring(0, index + 3);
    if (s.startsWith("-") == false) s = " " + s;
    return s;
  }
}
