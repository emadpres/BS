package com.shahin.test.server;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketAddress;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends Activity {
	DatagramSocket SOC = null;
	TextView tv;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		tv=(TextView) findViewById(R.id.server);
		//new ashghal2().execute();
		tv.setText("start");
		Thread server = new Thread(new Runnable() {

			@Override
			public void run() {
				while (true) {
					Log.i("server", "we are running :))");
					try {
						SOC = new DatagramSocket();
						// SOC=new DatagramSocket(6000);
						// SOC.setBroadcast(true)
						// SOC.bind(new InetSocketAddress(6000));
						byte[] message = "Hello Baby....".getBytes();
						DatagramPacket pack = new DatagramPacket(message,
								message.length,
								InetAddress.getByName("10.0.2.2"), 6000);
						SOC.send(pack);
						// SOC.close();
					} catch (Exception e) {
						Log.e("Server",
								"some thing wrong:-w / " + e.getMessage());
					}

					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						Log.e("server", "thread sucked");
					}
				}
			}
		});
		server.start();
	}

	@Override
	protected void onPause() {
		SOC.close();
		super.onPause();
	}
	
//	
//	public class ashghal2 extends AsyncTask<Void, Void, Void>{
//		String message="";
//		@Override
//		protected Void doInBackground(Void... params) {
//			byte[] temp = new byte[100];
//			try{
//				DatagramSocket socket=new DatagramSocket(5000);
//				Log.d("client","on thread");
//				//socket.connect(new InetSocketAddress(InetAddress.getByName("10.0.2.2"), 5000));
//				//Log.d("client","connect");
//				DatagramPacket pack=new DatagramPacket(temp, 100);
//				socket.receive(pack);
//				 Log.i("client","Hoooooooooooooooora !");
//		        Log.i("client",socket.toString()); 
//				message=pack.toString();
//				socket.close();
//			}
//			catch(Exception e){
//				Log.e("client","Error+ "+ e.getMessage());
//			}
//			return null;
//		}
//
//		@Override
//		protected void onPostExecute(Void result) {
//			tv.setText(message);
//			super.onPostExecute(result);
//		}
//
//		@Override
//		protected void onPreExecute() {
//			tv.setText("w8 for it");
//			super.onPreExecute();
//		}
//		
//	}

}
