/*
	��������QTableWidget��gridֻ���ƺ���Ĳ���

	by ���� 2016��9��26��13:12:31 @����
*/
#ifndef __QLINEDELEGATE_H__
#define __QLINEDELEGATE_H__

#include <QStyleditemDelegate>
#include <QTableView>
#include <QPen>

class QLineDelegate : public QStyledItemDelegate
{
public:
	QLineDelegate(QTableView* tableView);
protected:
	void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
	QPen pen;
	QTableView* view;
};

#endif // __QLINEDELEGATE_H__