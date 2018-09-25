print('loading file')

inspect=require('inspect')

dconv=require('dproto-conv-gen')
ddr_models = {ros2=true}
dconv.init_runtime(dprotofile,ddr_models)
DDBLX = dconv.DDBLX

--[[ Utilities of the runtime --]]
dblx = {}

--register data pointers as dblx
function register_dblx(dprotoname,id,cdata)
  dblx[id] = dconv.create_reference(dprotoname,cdata)
end

function get_dblx(id)
  return dblx[id]
end

function change_pointer(id,ud)
  dblx[id].dblx = ffi.cast(ffi.typeof(ud),ud)
end

print('looping')