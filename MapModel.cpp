//
// Created by programmer on 07.07.24.
//

#include "MapModel.h"
#include <QDebug>

MapModel::MapModel(QObject *parent)
        : QAbstractListModel(parent) {}

int MapModel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return m_data.count();
}

QVariant MapModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_data.count()) {
        return QVariant();
    }

    const DataItem &item = m_data[index.row()];

    switch (role) {
        case NameRole:
            return item.name;
        case ValueRole:
            return item.value;
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> MapModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ValueRole] = "value";
    return roles;
}

void MapModel::updateData(int index, const QVariant &value) {
    if (index < 0 || index >= m_data.count()) {
        qDebug() << "index not corrected: " << index;
        return;
    }

    m_data[index].value = value;
    emit dataChanged(this->index(index), this->index(index), { ValueRole });
}

void MapModel::setData(const QVariantList &data) {
    beginResetModel();
    m_data.clear();

    for (const QVariant &item : data) {
        QVariantMap map = item.toMap();
        QString name = map["name"].toString();
        QVariant value = map["value"];
        m_data.append({ name, value });
    }

    endResetModel();
}
