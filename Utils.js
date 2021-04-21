function expandChildrens(index)
{
    if (!index || !index.model)
    {
        return
    }

    if(!xmlTree.isExpanded(index))
    {
        xmlTree.expand(index)
    }
    for(var i=0; i < treeModel.rowCount(index); i++)
    {
        expandChildrens(treeModel.index(i,0, index))
    }
}

function expandAll()
{
    for(var i=0; i < treeModel.rowCount(); i++)
    {
         expandChildrens(treeModel.index(i,0))
    }
}
