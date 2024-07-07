//
// Created by programmer on 07.07.24.
//

#ifndef TESTAPP_MAPMODEL_H
#define TESTAPP_MAPMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QVariant>

class MapModel: public QAbstractListModel {
    Q_OBJECT

public:
    enum DataRoles {
        NameRole = Qt::UserRole + 1,
        ValueRole
    };

    MapModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void updateData(int index, const QVariant &value);
    Q_INVOKABLE void setData(const QVariantList &data);

private:
    struct DataItem {
        QString name;
        QVariant value;
    };

    QList<DataItem> m_data;
};


#endif //TESTAPP_MAPMODEL_H
