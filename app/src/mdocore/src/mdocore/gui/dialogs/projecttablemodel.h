#ifndef PROJECTProjectTableModel_H
#define PROJECTProjectTableModel_H


#include <QAbstractTableModel>
#include <QList>

#include <mdocore/models/project.h>

//! [0]

class ProjectTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    ProjectTableModel(QObject *parent = 0);
    ProjectTableModel(QList<Project *> projects, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<Project *> getProjects() const;

private:
    QList<Project *> projects;
};
//! [0]

#endif // PROJECTProjectTableModel_H
