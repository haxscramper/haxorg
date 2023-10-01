
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

function findXmakeParentDir(currentDir)
  currentDir = currentDir or os.curdir()

  local xmakeFile = path.join(currentDir, "xmake.lua")
  if os.isfile(xmakeFile) then
      return currentDir
  end

  local parentDir = path.directory(currentDir)
  if parentDir == currentDir then
      return nil
  end

  return findXmakeParentDir(parentDir)
end

function abs_build(...) return path.absolute(path.join(findXmakeParentDir(), "build", ...)) end

function abs_script(...) return path.absolute(path.join(findXmakeParentDir(), ...)) end

function iorun_stripped(cmd, args, ...)
  local result = os.iorunv(cmd, args, {...})
  return result:gsub("(%s+)$", "")  -- Remove trailing whitespace, including newlines
end


function error(text, ...)
  cprint(vformat("${red}[...]${clear} ") .. vformat(text, ...))
end

function warn(text, ...)
  cprint(vformat("${yellow}[...]${clear} ") .. vformat(text, ...))
end

function info(text, ...)
  cprint(vformat("${green}[...]${clear} ") .. vformat(text, ...))
end

function get_target_timestamps(target) 
  return path.absolute(path.join(config.buildir(), target:name() .. "_timestamps.txt"))
end

function detect_rebuld_state(target)
  import("core.project.config")
  import("core.base.option")

  local source_files = target:sourcefiles()
  local current_timestamps = {}
  local stored_timestamps_file = get_target_timestamps(target)
  
  for _, source_file in ipairs(source_files) do
      table.insert(current_timestamps, get_timestamp(source_file))
  end

  local stored_timestamps = { read_timestamps(stored_timestamps_file) }
  if #stored_timestamps ~= #current_timestamps then
      -- Number of files has changed; re-build necessary
      info("Number of files has changed for target '%s' from '%s' (now %s was %s), rebuilding ...", 
        target:name(),
        stored_timestamps_file,
        #current_timestamps,
        #stored_timestamps
      )
      return true
  end
  
  for i = 1, #current_timestamps do
      if tonumber(stored_timestamps[i]) < current_timestamps[i] then
          info("Timestamp has changed for %s, rebuilding %s ~= %s ...", 
            stored_timestamps_file[i],
            current_timestamps[i], 
            tonumber(stored_timestamps[i])
          )
          -- File has changed; re-build necessary
          return true
      end
  end
  
  -- No changes detected; skip build
  return false
end

function rebuild_guard(target, cbDo, cbNot, opts) 
  if detect_rebuld_state(target) then
    if not opts or opts["log"] then
      info("Detected changes in '%s', re-running ...", target:name())
    end
    cbDo(target)
    finalize_rebuild_state(target)
  else
    if not opts or opts["log"] then
      info("No changes detected for '%s', skipping.", target:name())
    end
    if cbNot then
      cbNot(target)
    end
  end
end

function finalize_rebuild_state(target)
  import("core.project.config")

  local source_files = target:sourcefiles()
  local timestamps = {}
  for _, source_file in ipairs(source_files) do
      table.insert(timestamps, get_timestamp(source_file))
  end

  local stored_timestamps_file = get_target_timestamps(target)
  write_timestamps(stored_timestamps_file, table.unpack(timestamps))
  info("Updated rebuild timestamps for '%s' to '%s'", target:name(), stored_timestamps_file)
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

function split(inputstr, sep)
  if sep == nil then
      sep = "%s" -- default to splitting on spaces
  end
  local t = {}
  for str in string.gmatch(inputstr, "([^" .. sep .. "]+)") do
      table.insert(t, str)
  end
  return t
end


function dict_map(tbl, f)
  local t = {}
  for k,v in pairs(tbl) do
      t[k] = f(v)
  end
  return t
end

function list_map(tbl, f)
  local t = {}
  for k,v in pairs(tbl) do
      table.insert(t, f(v))
  end
  return t
end


function maybe_try(command, except, finally, doWrap) 
  if doWrap then
    return try({command, except, finally})
  else
    local result = command()
    if finally then finally() end
    return result
  end
end
