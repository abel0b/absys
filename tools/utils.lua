function fexists(name)
   local f=io.open(name,"r")
   if f~=nil then io.close(f) return true else return false end
end

function merge_tables(ta, tb)
    for k, v in pairs(tb) do
        ta[k] = v
    end
end

