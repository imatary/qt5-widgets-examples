#ifndef __VSC_LOADING_HPP__
#define __VSC_LOADING_HPP__

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QMovie>
#include <QThread>




class VSCLoading : public QWidget
{
	Q_OBJECT
public:
	VSCLoading(QWidget *parent);
	~VSCLoading();
public:
	void Processing(int cnt);
	static VSCLoading * Create();
private:
	QLabel * m_label;
	QMovie * m_movie;
};


#endif // __VSC_LOADING_HPP__