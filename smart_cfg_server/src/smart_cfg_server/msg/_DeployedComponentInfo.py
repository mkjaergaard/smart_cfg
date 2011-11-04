"""autogenerated by genmsg_py from DeployedComponentInfo.msg. Do not edit."""
import roslib.message
import struct

import smart_cfg_server.msg

class DeployedComponentInfo(roslib.message.Message):
  _md5sum = "3305c66fb574429273ccdb8681ca5650"
  _type = "smart_cfg_server/DeployedComponentInfo"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """DeployedComponentID id
ComponentModelID model_id
ParameterIDAndValueEx[] parameters

================================================================================
MSG: smart_cfg_server/DeployedComponentID
string name
================================================================================
MSG: smart_cfg_server/ComponentModelID
string name
================================================================================
MSG: smart_cfg_server/ParameterIDAndValueEx
ParameterID id
ParameterValue current_value
bool change_request
ParameterValue new_value
================================================================================
MSG: smart_cfg_server/ParameterID
string name
================================================================================
MSG: smart_cfg_server/ParameterValue
string type
string encoded_value
"""
  __slots__ = ['id','model_id','parameters']
  _slot_types = ['smart_cfg_server/DeployedComponentID','smart_cfg_server/ComponentModelID','smart_cfg_server/ParameterIDAndValueEx[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       id,model_id,parameters
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(DeployedComponentInfo, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.id is None:
        self.id = smart_cfg_server.msg.DeployedComponentID()
      if self.model_id is None:
        self.model_id = smart_cfg_server.msg.ComponentModelID()
      if self.parameters is None:
        self.parameters = []
    else:
      self.id = smart_cfg_server.msg.DeployedComponentID()
      self.model_id = smart_cfg_server.msg.ComponentModelID()
      self.parameters = []

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      _x = self.id.name
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.model_id.name
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      length = len(self.parameters)
      buff.write(_struct_I.pack(length))
      for val1 in self.parameters:
        _v1 = val1.id
        _x = _v1.name
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _v2 = val1.current_value
        _x = _v2.type
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v2.encoded_value
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        buff.write(_struct_B.pack(val1.change_request))
        _v3 = val1.new_value
        _x = _v3.type
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v3.encoded_value
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error, se: self._check_types(se)
    except TypeError, te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      if self.id is None:
        self.id = smart_cfg_server.msg.DeployedComponentID()
      if self.model_id is None:
        self.model_id = smart_cfg_server.msg.ComponentModelID()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.id.name = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.model_id.name = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.parameters = []
      for i in xrange(0, length):
        val1 = smart_cfg_server.msg.ParameterIDAndValueEx()
        _v4 = val1.id
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        _v4.name = str[start:end]
        _v5 = val1.current_value
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        _v5.type = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        _v5.encoded_value = str[start:end]
        start = end
        end += 1
        (val1.change_request,) = _struct_B.unpack(str[start:end])
        val1.change_request = bool(val1.change_request)
        _v6 = val1.new_value
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        _v6.type = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        _v6.encoded_value = str[start:end]
        self.parameters.append(val1)
      return self
    except struct.error, e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      _x = self.id.name
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self.model_id.name
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      length = len(self.parameters)
      buff.write(_struct_I.pack(length))
      for val1 in self.parameters:
        _v7 = val1.id
        _x = _v7.name
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _v8 = val1.current_value
        _x = _v8.type
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v8.encoded_value
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        buff.write(_struct_B.pack(val1.change_request))
        _v9 = val1.new_value
        _x = _v9.type
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v9.encoded_value
        length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error, se: self._check_types(se)
    except TypeError, te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      if self.id is None:
        self.id = smart_cfg_server.msg.DeployedComponentID()
      if self.model_id is None:
        self.model_id = smart_cfg_server.msg.ComponentModelID()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.id.name = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.model_id.name = str[start:end]
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.parameters = []
      for i in xrange(0, length):
        val1 = smart_cfg_server.msg.ParameterIDAndValueEx()
        _v10 = val1.id
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        _v10.name = str[start:end]
        _v11 = val1.current_value
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        _v11.type = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        _v11.encoded_value = str[start:end]
        start = end
        end += 1
        (val1.change_request,) = _struct_B.unpack(str[start:end])
        val1.change_request = bool(val1.change_request)
        _v12 = val1.new_value
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        _v12.type = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        _v12.encoded_value = str[start:end]
        self.parameters.append(val1)
      return self
    except struct.error, e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_B = struct.Struct("<B")
