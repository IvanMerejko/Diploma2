function expandChildrens(view, model, index)
{
    if (!index || !index.model)
    {
        return
    }

    if(!view.isExpanded(index))
    {
        view.expand(index)
    }
    for(var i=0; i < model.rowCount(index); i++)
    {
        expandChildrens(model.index(i,0, index))
    }
}

function expandAll(view, model)
{
    for(var i=0; i < model.rowCount(); i++)
    {
         expandChildrens(view, model, model.index(i,0))
    }
}
