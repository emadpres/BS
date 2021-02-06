package com.network.eawifi;

import java.io.File;
import java.util.ArrayList;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class SelectFileDialog extends Activity{
	
	private String currentPath;
	private File file;
	private File[] files;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		setContentView(R.layout.select_file_layout);
		super.onCreate(savedInstanceState);
		
		currentPath=Environment.getExternalStorageDirectory().toString();
		final ArrayList<String> path=new ArrayList<String>();
		file= new File(currentPath);
		files=file.listFiles();
		getItem(files,path);
		ListView lv=(ListView) findViewById(R.id.dialog_list);
		final BrowseFileList adapter=new BrowseFileList(SelectFileDialog.this, path);
		lv.setAdapter(adapter);
		lv.setOnItemClickListener(new OnItemClickListener() {

			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				if (arg3 != 0) {												// not up button
					if (files[(int) arg3 - 1].isFile()) {						//the selected is a file
						Intent intent = new Intent();
						intent.putExtra("get", files[(int) (arg3 - 1)]
								.getPath().toString());
						setResult(RESULT_OK, intent);
						finish();
					} else {													//the selected is a folder
						currentPath = files[(int) (arg3 - 1)].getPath()
								.toString();
						file = new File(currentPath);
						files = file.listFiles();
						getItem(files, path);
						adapter.notifyDataSetChanged();
					}
				} else {														//up button
					if (currentPath.equals(Environment.getExternalStorageDirectory().toString())) {			//in root
						Toast.makeText(SelectFileDialog.this,
								"you are in the Root", Toast.LENGTH_SHORT)
								.show();
					} else {												//in folder
						currentPath = currentPath.substring(0,
								currentPath.lastIndexOf("/"));
						file = new File(currentPath);
						files = file.listFiles();
						getItem(files, path);
						adapter.notifyDataSetChanged();
					}
				}
			}
		});
		
		Button ok=(Button) findViewById(R.id.dialog_ok);
		ok.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				Intent intent=new Intent();
				intent.putExtra("get","");
				setResult(RESULT_CANCELED, intent);
				finish();
			}
		});

	}

	private class BrowseFileList extends ArrayAdapter<String> {

		ArrayList<String> str;
		private Context context;

		public BrowseFileList(Context context, ArrayList<String> s) {
			super(context, R.layout.browselist, s);
			this.context = context;
			this.str = s;
			// TODO Auto-generated constructor stub
		}

		class ViewHolder {
			public ImageView iv;
			public TextView tv;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			View v = convertView;
			if (v == null) {
				ViewHolder holder = new ViewHolder();
				LayoutInflater inf = (LayoutInflater) context
						.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
				v = inf.inflate(R.layout.browselist, parent, false);
				holder.iv = (ImageView) v.findViewById(R.id.browse_image);
				holder.tv = (TextView) v.findViewById(R.id.browse_address);
				v.setTag(holder);
			}
			ViewHolder hold = (ViewHolder) v.getTag();
			if (position == 0) {
				hold.iv.setImageResource(R.drawable.up);
				hold.tv.setText("Up...");
			} else {
				if (str.get(position).substring(0, 6).equals("folder")) {
					hold.iv.setImageResource(R.drawable.folder);
				} else {
					hold.iv.setImageResource(R.drawable.file_new);
				}
				hold.tv.setText(str.get(position).substring(6));
			}

			return v;
		}

	}
	private void getItem(File f[],ArrayList<String> str){
		str.clear();
		str.add("up");
		for(int i=0;i<f.length;i++){
			if(f[i].isDirectory()){
				str.add("folder"+f[i].getName().toString());
			}else{
				str.add("file.."+f[i].getName().toString());
			}
		}
		
	}
}
