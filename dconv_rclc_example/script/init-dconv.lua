print('LOADING RUNTIME')

dconv=require('dproto-conv-gen')
ddr_models = {ros2=true}
dconv.init_runtime(dprotofile,ddr_models)

--[[ Utilities of the runtime --]]
local dblx = {}

--register data pointers as dblx
function register_dblx(dprotoname,id,cdata)
  dblx[id] = dconv.create_reference(dprotoname,cdata)
end

function get_dblx(id)
  return dblx[id]
end

function change_pointer(id,ud)
  local data = ud
  if type(ud) == 'userdata' then
     data = ffi.cast('geometry_msgs__msg__Point*',ud)
  end
  dblx[id].dblx = ffi.cast(ffi.typeof(data),data)
end

function convert(src,tgt)
  local src = dblx[src]
  local tgt = dblx[tgt]
  dconv.convert(src,tgt)
end
  
  
print('RUNTIME READY')