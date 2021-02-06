package com.shahin.test.playvideo;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.RandomAccessFile;

import android.app.Activity;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.widget.MediaController;
import android.widget.VideoView;

public class MainActivity extends Activity {

	VideoView video;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		File file=new File(Environment.getExternalStorageDirectory().getPath()+"/test.mp4");
		File source=new File(Environment.getExternalStorageDirectory().getPath()+"/f.3gp");
		try {
			file.createNewFile();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
//		for(int i=0;i<(source.length()/2048)+20;i++){
//			byte[] data=new byte[1024];
//			data=ReadFile(source, i*1024, 1024);
//			WriteFile(file, data, i*1024);
//		}
		try {
			RandomAccessFile raf=new RandomAccessFile(file, "rw");
			raf.setLength(source.length());
			raf.close();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		video=(VideoView) findViewById(R.id.videoView1);

		video.setVideoPath(file.getPath().toString());
		MediaController mc=new MediaController(this);
		video.setMediaController(mc);
		video.start();
//		MediaPlayer mp=new MediaPlayer();
//		try {
//			mp.setDataSource(file.getPath().toString());
//			mp.prepare();
//			mp.start();
//		} catch (Exception e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		} 
		

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
	public byte[] ReadFile(File f, int offset, int count) {
		byte[] data = new byte[1024];

		try {
			FileInputStream fis = new FileInputStream(f);
			Log.w("on read","FileInputStream Create");
			fis.skip(offset);
			if (fis != null) {
				fis.read(data, 0, count);
				fis.close();
			}
		} catch (Exception e) {
			Log.e("error in Reading...", e.getMessage().toString()+" / "+e.getLocalizedMessage().toString());
		}
		return data;
	}

	public void WriteFile(File f, byte[] data, int offset) {
		
		try {
			RandomAccessFile rf=new RandomAccessFile(f, "rw");
			rf.seek(offset);
			rf.write(data);
			rf.close();
//			FileOutputStream fos = new FileOutputStream(f);
//			fos.write(data, 0, data.length);
//			fos.flush();
//			fos.close();
		} catch (Exception e) {
			Log.e("error in writting...", e.getMessage().toString());
		}
	}

}
