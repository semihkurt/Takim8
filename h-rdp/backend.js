// backend.js
.pragma library

function validateUserCredentials(uname, pword)
{
    var ret
    if(uname === "" || pword === "")
    {
        ret = 1
    }
    else
    {
        ret = 0
    }
    return ret
}

function validateRegisterCredentials(uname, pword, pword2, hint)
{
    var ret
    if(uname === "" || pword === "" || pword2 === "" || hint === "")
    {
        ret = 1
        return ret
    }
    else if(pword !== pword2)
    {
        ret = 2
    }
    else
    {
        ret = 0
    }
    return ret
}
