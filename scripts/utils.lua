
-- Function to get the current timestamp of a file
function get_timestamp(filepath)
  return os.mtime(filepath)
end

-- Function to read timestamps from a file
function read_timestamps(filename)
  if os.isfile(filename) then
    local content = io.readfile(filename)
    if content then
        return table.unpack(content:split('\n'))
    end
  end

  return nil
end

-- Function to write timestamps to a file
function write_timestamps(filename, ...)
  local content = table.concat({...}, '\n')
  io.writefile(filename, content)
end

function with_dir(directory, callback)
  local olddir = os.curdir()
  os.cd(directory)
  callback()
  os.cd(olddir)
end

function info(text, ...)
  cprint(vformat("${green}[...]${clear} ") .. vformat(text, ...))
end

function detect_rebuld_state(target)
  import("core.project.config")
  import("core.base.option")

  local source_files = target:sourcefiles()
  local current_timestamps = {}
  local stored_timestamps_file = path.join(config.buildir(), "timestamps.txt")
  
  for _, source_file in ipairs(source_files) do
      table.insert(current_timestamps, get_timestamp(source_file))
  end

  local stored_timestamps = { read_timestamps(stored_timestamps_file) }
  if #stored_timestamps ~= #current_timestamps then
      -- Number of files has changed; re-build necessary
      info("Number of files has changed, rebuilding ...")
      return true
  end
  
  for i = 1, #current_timestamps do
      if tonumber(stored_timestamps[i]) < current_timestamps[i] then
          info("Timestamp as changed, rebuilding %s ~= %s ...", current_timestamps[i], tonumber(stored_timestamps[i]))
          -- File has changed; re-build necessary
          return true
      end
  end
  
  -- No changes detected; skip build
  return false
end

function rebuild_quard(target, cbDo, cbNot) 
  if detect_rebuld_state(target) then
    cbDo(target)
  elseif cbNot then
    cbNot(target)
  end
  finalize_rebuild_state(target)
end

function finalize_rebuild_state(target)
  import("core.project.config")

  local source_files = target:sourcefiles()
  local timestamps = {}
  for _, source_file in ipairs(source_files) do
      table.insert(timestamps, get_timestamp(source_file))
  end

  local stored_timestamps_file = path.join(config.buildir(), "timestamps.txt")
  write_timestamps(stored_timestamps_file, table.unpack(timestamps))
end

function tuple_iter(tuples)
  local i = 0
  return function()
      i = i + 1
      if tuples[i] then
          return unpack(tuples[i])
      end
  end
end

function def_option(name, doc, default)
  option(name)
    set_description(doc)
    set_default(default)
  option_end()
end
