#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QFrame>
#include <QGridLayout>

class MyButton: public QPushButton{
public:
		MyButton():QPushButton(){}
		MyButton(QIcon icon,QString text):QPushButton(icon,text){}
private:
		void	mousePressEvent ( QMouseEvent * e ){
			setText("I Am Clicked");
		}
};

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	QMainWindow* win = new QMainWindow();
	win->showMaximized();

	QFrame* f = new QFrame();
	QGridLayout* l = new QGridLayout();
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			 l->addWidget(new MyButton(QIcon("test.png"),"Salaam") ,
				i,j);
	
	f->setLayout(l);
	win->setCentralWidget(f);
	
	
	return a.exec();
}

