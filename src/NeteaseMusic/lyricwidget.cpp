﻿#include "lyricwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDir>
#include <QSettings>
#include <QPainter>
#include <QStyleOption>
#include <QDebug>

LyricWidget::LyricWidget(QWidget *parent) : QWidget(parent)
{
    resize(700, 100);
    isMouseOn = false;
    isMLBD = false;
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool | Qt::X11BypassWindowManagerHint);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(0);
    vbox->setMargin(2);
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addStretch();
    pushButton_set = new QPushButton;
    pushButton_set->setFixedSize(24, 24);
    pushButton_set->setIcon(QIcon(":/set.svg"));
    pushButton_set->setFocusPolicy(Qt::NoFocus);
    pushButton_set->setFlat(true);
    pushButton_set->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_set);
    pushButton_close = new QPushButton;
    pushButton_close->setFixedSize(24, 24);
    pushButton_close->setIcon(QIcon(":/close.svg"));
    pushButton_close->setFocusPolicy(Qt::NoFocus);
    pushButton_close->setFlat(true);
    pushButton_close->setCursor(Qt::PointingHandCursor);
    hbox->addWidget(pushButton_close);
    vbox->addLayout(hbox);
    vbox->addStretch();
    setLayout(vbox);
    pushButton_set->hide();
    pushButton_close->hide();
}

void LyricWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isMLBD = true;
        m_point = event->pos();
    }
}

void LyricWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isMLBD) {
        setCursor(Qt::ClosedHandCursor);
        move(event->pos() - m_point + pos());
        //qDebug() << event->pos() << m_point << pos();
    }
}

void LyricWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    isMLBD = false;
    setCursor(Qt::ArrowCursor);
    writeSettings(QDir::currentPath() + "/config.ini", "config", "LyricX", QString::number(x()));
    writeSettings(QDir::currentPath() + "/config.ini", "config", "LyricY", QString::number(y()));
}

void LyricWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    pushButton_close->setVisible(true);
    pushButton_set->setVisible(true);
    isMouseOn = true;
    update();
}

void LyricWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    //setStyleSheet("");
    pushButton_close->setVisible(false);
    pushButton_set->setVisible(false);
    isMouseOn = false;
    update();
}

void LyricWidget::writeSettings(QString path, QString group, QString key, QString value)
{
    QSettings *config = new QSettings(path, QSettings::IniFormat);
    config->beginGroup(group);
    config->setValue(key, value);
    config->endGroup();
}

void LyricWidget::paintEvent(QPaintEvent *event)
{
    // https://bbs.csdn.net/topics/350233731
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);

    // 鼠标悬停绘制透明背景
    if (isMouseOn) {
        p.setBrush(QColor(255, 255, 255, 20));
        p.drawRect(rect());
    }

    // 根据字体计算歌词宽度
    QFontMetrics FM(font);
    QRegion left(0, 30, FM.boundingRect(text).width()*lp, height());     //左边唱过的区域
    QRegion right(FM.boundingRect(text).width()*lp, 30, width(), height()); //右边未唱过的区域
    QPainterPath path;
    path.addText(0, 75, font, text); //歌词文字作为路径
    p.setBrush(color_left);         //文字填充颜色
    //p.setPen(QColor(Qt::black));  //文字边框颜色
    p.setClipRegion(left);          //设置栽剪区域,Painter只在其中绘图
    p.drawPath(path);               //画出左边歌词
    p.setBrush(color_right);        //改变填充字体颜色为绿色
    //p.setPen(QColor(Qt::black));  //改变字体边框为绿色
    p.setClipRegion(right);         //设置栽剪区域为右边未唱过的部分
    p.drawPath(path);               //画右边未唱过的歌词
}
