#include "cchart.h"

CChart::CChart(QMap<QString,int> list ,QWidget *parent)
	: QWidget(parent)
{
	this->list = list;
	setMinimumWidth(list.size() * 20  + 100);
	setFixedHeight (450);
}

CChart::~CChart()
{

}

void CChart::paintEvent( QPaintEvent *e )
{
	QPainter* painter = new QPainter(this);
	painter->drawRect(0, 0, this->width() - 1,this->height() - 1);

	double tmp =-100;
	QMap<QString , int>::Iterator i;
	for (i = list.begin() ; i != list.end() ; ++i)
	{
		if (tmp < i.value())
			tmp = i.value();
	}
	tmp--;


		double max = 0;

		while (tmp > 0)
		{
			max = max + 1;
				tmp /= 10;
		}
	

		int color = 1;
		tmp = 0;
		for (i = list.begin() ; i != list.end() ; ++i)
		{
			QColor* c = new QColor((color & 1) * 200, (color & 2) * 100, (color & 4) * 50); 
			painter->fillRect(55 + tmp * 20, 325, 10, -300 * i.value() / qPow(10, max), QBrush(*c));
			painter->drawText(55 + tmp * 20, 315 - 300 * i.value() / qPow(10, max), QString::number(i.value()));
			color = color * 2;
				tmp = tmp + 1;

				if (color == 8)
					color = 1;
		}

		painter->save();
		painter->rotate(-90);

			tmp = 0;

			for (i = list.begin() ; i != list.end() ; ++i)
			{
				painter->drawText(25 - this->width(), 52 + tmp * 20, 95, 15, 0, i.key());
					tmp = tmp + 1;
			}
		
			painter->restore();
}
