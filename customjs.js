function Decode(fPort, bytes) {
  var str = "";

  for(var index = 0; index < bytes.length; index += 1)
    str += String.fromCharCode(bytes[index]);
  
  return {"a" : str, "len" : bytes.length};
}