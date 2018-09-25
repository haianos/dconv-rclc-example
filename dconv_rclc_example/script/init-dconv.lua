print('LOADING RUNTIME')

dconv=require('dproto-conv-gen')
ddr_models = {ros2=true}
dconv.init_runtime(dprotofile,ddr_models)

--[[ Utilities of the runtime --]]
-- NOTE to users: do not change the above.
-- It will be merged as Lua module.
local dblx   = {}
local ctypes = {} --caching ctype name resolution from ddr

--register data pointers as dblx
function register_dblx(dprotoname,id,cdata)
  dblx[id]  = dconv.create_reference(dprotoname,cdata)
  local ddr  = dblx[id].dproto.ddr
  ctypes[id] = dconv.get_ctype(ddr)  -- caching ctype
end

function get_dblx(id)
  return dblx[id].dblx
end

function change_ref(id,ud)
  local data = ud
  if type(ud) == 'userdata' then
    data = ffi.cast(ctypes[id],ud)
  end
  dblx[id].dblx = ffi.cast(ffi.typeof(data),data)
end

function convert(src,tgt)
  local src = dblx[src]
  local tgt = dblx[tgt]
  dconv.convert(src,tgt)
end
  
  
print('RUNTIME READY')