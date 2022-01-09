#include "projecttablemodel.h"


ProjectTableModel::ProjectTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

ProjectTableModel::ProjectTableModel(QList<Project *> projects, QObject *parent)
    : QAbstractTableModel(parent)
    , projects(projects)
{
}

int ProjectTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return projects.size();
}

int ProjectTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant ProjectTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= projects.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &project = projects.at(index.row());

        if (index.column() == 0)
            return project->getName();
        else if (index.column() == 1)
            return project->getDescription();
        else if (index.column() == 2)
            return project->getIsDefault();
        else if (index.column() == 3)
            return project->getTags();
    }
    return QVariant();
}

QVariant ProjectTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Name");

        case 1:
            return tr("Description");

        case 2:
            return tr("Default");

        case 3:
            return tr("Tags");

        default:
            return QVariant();
        }
    }
    return QVariant();
}

bool ProjectTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        //        projects.insert(position, { QString(), QString() });

        endInsertRows();
    return true;
}

bool ProjectTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        projects.removeAt(position);

    endRemoveRows();
    return true;
}

bool ProjectTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        auto project = projects.value(row);

        if (index.column() == 0)
            project->setName(value.toString());
        else if (index.column() == 1)
            project->setTags(value.toString());
        else
            return false;

        //        projects.replace(row, project);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

Qt::ItemFlags ProjectTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList<Project *> ProjectTableModel::getProjects() const
{
    return projects;
}
