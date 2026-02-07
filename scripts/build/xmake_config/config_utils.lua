function get_project_dir()
  return path.normalize(path.absolute(path.join(os.scriptdir(), "../../..")))
end
