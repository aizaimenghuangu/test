#include "mychart1.h"

#include <QDateTime>

myChart1::myChart1(QWidget *parent) :
    QWidget(parent)
{
    this->initVariables();
}

void myChart1::initVariables()
{
    m_bUseAntialiasing=true;
    m_bShowHLine=true;
    m_bShowPoint=true;
    m_hLineClr=Qt::black;
    m_strTitle="正在初始化……";
}

void myChart1::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);

    if(m_bUseAntialiasing)
    {
        painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    }

    resetVariables(&painter);
    drawBackground(&painter);
    drawBox(&painter);
    drawText(&painter);
    drawGraph(&painter);
    drawTitle(&painter);
}


void myChart1::resetVariables(QPainter *painter)
{
    QPointF topRectTopLeftPot(0,0);
    QPointF topRectBottomRightPot(width(),height()/3*2);
    m_topRect=QRectF(topRectTopLeftPot,topRectBottomRightPot);

    QPointF bottomRectTopLeftPot(0,height()/3*2);
    QPointF bottomRectBottomRightPot(width(),height());
    m_bottomRect=QRectF(bottomRectTopLeftPot,bottomRectBottomRightPot);

    m_leftSpace=(qreal)width()/10;
    m_topSpace=(qreal)height()/10;
}

void myChart1::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient topGradient(m_topRect.topLeft(),m_topRect.bottomLeft());
    topGradient.setColorAt(0.0,QColor(255,255,255));
    topGradient.setColorAt(1.0,QColor(255,255,255));
    painter->setBrush(topGradient);
    painter->drawRect(m_topRect);

    QLinearGradient bottomGradient(m_bottomRect.topLeft(),m_bottomRect.bottomLeft());
    bottomGradient.setColorAt(0.0,QColor(255,255,255));
    bottomGradient.setColorAt(1.0,QColor(255,255,255));
    painter->setBrush(bottomGradient);
    painter->drawRect(m_bottomRect);
    painter->restore();
}

void myChart1::drawBox(QPainter *painter)
{
    painter->save();
    QPointF topLeftPot(m_leftSpace,m_topSpace);
    QPointF bottomRightPot(width()-m_leftSpace,height()-m_topSpace);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::NoBrush);

    m_boxRect=QRectF(topLeftPot,bottomRightPot);
    painter->drawRect(m_boxRect);

    if(m_bShowHLine)
    {
        painter->setPen(m_hLineClr);
        qreal increment=(qreal)m_boxRect.height()/10;
        qreal startY=m_boxRect.topLeft().y();
        qreal boxWidth=m_boxRect.width();
        for(int i=0;i<9;i++)
        {
            startY+=increment;
            QPointF leftPot(m_boxRect.topLeft().x(),startY);
            QPointF rightPot(m_boxRect.topRight().x(),startY);
            painter->setPen(Qt::DotLine);
            painter->drawLine(leftPot,rightPot);
        }
    }
    painter->restore();
}

void myChart1::drawText(QPainter *painter)
{
    painter->save();

    int value=100;
    qreal increment=(qreal)m_boxRect.height()/10;
    qreal startY=m_boxRect.topLeft().y();
    QString strValue;
    for(int i=0;i<=10;i++)
    {
        strValue=tr("%1%").arg(value);
        qreal textWidth=fontMetrics().width(strValue);
        qreal textHeight=fontMetrics().height();

        QPointF textPot(m_boxRect.topLeft().x()-TEXT_BOX_SPACE-textWidth,startY+textHeight/2);
        painter->drawText(textPot,strValue);

        value-=10;
        startY+=increment;
    }

    painter->restore();
}

void myChart1::drawGraph(QPainter *painter)
{
    painter->save();
    qreal startX=m_boxRect.topRight().x();
    QVector<QPointF> potVec;
    painter->save();
    painter->setPen(Qt::NoPen);
    potVec.push_back(QPointF(startX,m_boxRect.bottomRight().y()));
    for(int i=0;i<m_dataVec.count();i++)
    {
        qreal x=startX;
        qreal y=m_boxRect.bottomRight().y()-(qreal)m_dataVec.at(i)*(m_boxRect.height()/100);
        QPointF dataPot(x,y);
        potVec.push_back(dataPot);
        startX-=X_INCREMENT;

    }
    potVec.push_back(QPointF(startX,m_boxRect.bottomRight().y()));
    painter->restore();

        QLinearGradient graphGradient(m_boxRect.topLeft(),m_boxRect.bottomLeft());
        graphGradient.setColorAt(0.0,QColor(240,67,51));
        graphGradient.setColorAt(0.4,QColor(208,94,49));
        graphGradient.setColorAt(1.0,QColor(85,255,0));
        painter->setBrush(graphGradient);
        painter->setPen(Qt::NoPen);
        painter->drawConvexPolygon(QPolygonF(potVec));

    // draw line
    if(m_bShowPoint)
    {
        QPointF startPoint;
        QPointF endPoint;
        painter->setOpacity(0.5);
        for(int i = 1;i < potVec.count()-1; i++)
        {
            startPoint=potVec.at(i);
            if(i == potVec.count())
            {
                endPoint=potVec.at(i);
            }
            else
            {
                endPoint=potVec.at(i+1);
            }
            painter->setBrush(Qt::blue);
            painter->setPen(Qt::blue);
            painter->drawLine(startPoint, endPoint);
            QPoint point(startPoint.x(), 0);
//            qDebug() << point;
            painter->drawText(point, "1908878998");

        }
    }
    painter->restore();
}

void myChart1::drawTime(QPainter *painter)
{
    painter->save();
    qreal titleX=(qreal)width()/2;
    qreal titleY=m_topSpace/2;
    qreal textWidth=fontMetrics().width(m_strTitle);
    qreal textHeight=fontMetrics().height();

    QFont titleFont;
    titleFont.setBold(true);
    titleFont.setPointSize(10);
    painter->setFont(titleFont);

    QPointF textPot(titleX-textWidth/2,titleY/2+textHeight/2);
    painter->drawText(textPot, QTime::currentTime().toString());
    painter->restore();
}

void myChart1::drawTitle(QPainter *painter)
{
    painter->save();
    qreal titleX=(qreal)width()/2;
    qreal titleY=m_topSpace/2;
    qreal textWidth=fontMetrics().width(m_strTitle);
    qreal textHeight=fontMetrics().height();

    QFont titleFont;
    titleFont.setBold(true);
    titleFont.setPointSize(10);
    painter->setFont(titleFont);

    QPointF textPot(titleX-textWidth/2,titleY/2+textHeight/2);
    painter->drawText(textPot,m_strTitle);
    painter->restore();
}


void myChart1::addData(qreal data)
{
    m_dataVec.push_front(data);
    updateVector();
}

void myChart1::updateVector()
{
    int allowDataCount=m_boxRect.width()/X_INCREMENT;

    if(m_dataVec.count()>allowDataCount)
    {
        m_dataVec.remove(allowDataCount,1);
    }
    update();
}
