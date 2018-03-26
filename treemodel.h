#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QString>

class TreeItem;

class TreeModel : public QAbstractItemModel{

    Q_OBJECT

    TreeItem *rootItem;

public:

    QString filename;

    TreeModel(const QStringList &headers, const QString &data, QObject *parent = 0);

    ~TreeModel();

    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    virtual bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex()) override;
    virtual bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex()) override;

    virtual bool insertRows(int position, int rows,const QModelIndex &parent = QModelIndex()) override;
    virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

private:
    void setupModelData(const QStringList &lines, TreeItem *parent);

    TreeItem *getItem(const QModelIndex &index) const;
};

#endif // TREEMODEL_H

