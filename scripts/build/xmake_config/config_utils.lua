function get_project_dir()
  return path.normalize(path.absolute(path.join(os.scriptdir(), "../../..")))
end

function get_autogen_dir()
  local result = path.normalize(path.absolute(
                                    get_config("autogen_build_dir") or
                                        path.join(get_config("builddir"),
                                                  "autogen")))

  return result
end
