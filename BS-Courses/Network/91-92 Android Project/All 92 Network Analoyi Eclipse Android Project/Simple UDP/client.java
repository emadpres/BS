package com.shahin.test.clientside;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.InetSocketAddress;

import android.app.Activity;
import android.content.res.Resources.Theme;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {
	TextView tv,tv2;
	DatagramSocket socket;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		tv=(TextView) findViewById(R.id.tv1);
		tv2=(TextView) findViewById(R.id.textView1);
		tv.setTextSize(20);
		Log.d("client","start");
		Button btn=(Button) findViewById(R.id.button1);
		btn.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				new receive().execute();
				//new receive2().execute();
				
			}
		});
	}

public class receive extends AsyncTask<Void, Void, Void> {
	String message="";
	
	
	@Override
	protected void onPreExecute() {
		tv.setText("w8 for receive....:-w");
		super.onPreExecute();
	}

	@Override
	protected Void doInBackground(Void... params) {
		byte[] temp = new byte[100];
		try{
			DatagramSocket socket=new DatagramSocket(5000);
			Log.d("client","on thread-5000");
			//socket.connect(new InetSocketAddress(InetAddress.getByName("10.0.2.2"), 5000));
			//Log.d("client","connect");
			DatagramPacket pack=new DatagramPacket(temp, 100);
			socket.receive(pack);
			 Log.i("client","Hoooooooooooooooora !");
	        Log.i("client","length="+pack.getLength()); 
			message=new String(pack.getData());
			//socket.close();
		}
		catch(Exception e){
			Log.e("client","Error+ "+ e.getMessage());
		}
		return null;
	}

	@Override
	protected void onPostExecute(Void result) {
		tv.setText(message);
		tv.append("\nyess baby!");
		super.onPostExecute(result);
	}
	
}

@Override
protected void onPause() {
	socket.close();
	super.onPause();
}

public class receive2 extends AsyncTask<Void, Void, Void> {
	String message="";
	
	
	@Override
	protected void onPreExecute() {
		tv2.setText("w8 for receive....:-w");
		super.onPreExecute();
	}

	@Override
	protected Void doInBackground(Void... params) {
		byte[] temp = new byte[100];
		try{
			DatagramSocket socket=new DatagramSocket(6000);
			Log.d("client","on thread-6000");
			//socket.connect(new InetSocketAddress(InetAddress.getByName("10.0.2.2"), 5000));
			//Log.d("client","connect");
			DatagramPacket pack=new DatagramPacket(temp, 100);
			socket.receive(pack);
			 Log.i("client","Hoooooooooooooooora !");
	        Log.i("client",socket.toString()); 
			message=pack.toString();
			//socket.close();
		}
		catch(Exception e){
			Log.e("client","Error+ "+ e.getMessage());
		}
		return null;
	}

	@Override
	protected void onPostExecute(Void result) {
		tv2.setText(message);
		tv2.append("\nyess baby!");
		super.onPostExecute(result);
	}
	
}

}
