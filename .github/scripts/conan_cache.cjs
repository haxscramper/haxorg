const fs   = require("node:fs/promises");
const path = require("node:path");

module.exports = async function run({core}) {
  const cache = require(
      path.join(
          process.env.RUNNER_TEMP,
          "conan-cache-client",
          "node_modules",
          "@actions/cache",
          ),
  );

  const payload = JSON.parse(process.env.ACTION_PAYLOAD);
  const root    = path.join(process.env.RUNNER_TEMP, "conan-package-cache");
  const metadataPath = path.join(
      process.env.RUNNER_TEMP,
      "conan-package-cache-restored.json",
  );

  function prefix(packageName) { return `conan-package-v1${packageName}--`; }

  function key(packageName) {
    return `${prefix(packageName)}${payload.run_id}-${payload.run_attempt}`;
  }

  function directory(packageName) { return path.join(root, packageName); }

  async function restore(packageName, required) {
    const restoreKeys = required
                            ? [ `${prefix(packageName)}${payload.run_id}-` ]
                            : [ prefix(packageName) ];

    const restoredKey = await cache.restoreCache(
        [ directory(packageName) ],
        key(packageName),
        restoreKeys,
    );

    if (!restoredKey) {
      if (required) {
        throw new Error(
            `No upstream Conan cache found for ${packageName} in run ${
                payload.run_id}`,
        );
      }

      core.info(`No previous Conan cache found for ${packageName}`);
      return null;
    }

    await fs.access(path.join(directory(packageName), "package.tgz"));
    core.info(`Restored ${packageName}: ${restoredKey}`);
    return restoredKey;
  }

  if (payload.operation === "restore") {
    const restored = {};

    if (!payload.python_package) {
      restored[payload.package] = await restore(payload.package, false);
    }

    for (const packageName of new Set(payload.incoming_packages)) {
      restored[packageName] = await restore(packageName, true);
    }

    await fs.writeFile(metadataPath, JSON.stringify(restored));
    return;
  }

  if (payload.operation === "save") {
    const restored = JSON.parse(
        await fs.readFile(metadataPath, "utf8"),
    );
    const currentKey = key(payload.package);

    if (restored[payload.package] === currentKey) {
      core.info(`Cache already exists: ${currentKey}`);
      return;
    }

    await fs.access(path.join(directory(payload.package), "package.tgz"));

    const cacheId = await cache.saveCache(
        [ directory(payload.package) ],
        currentKey,
    );

    if (!(cacheId > 0)) {
      throw new Error(`Failed to save Conan cache: ${currentKey}`);
    }

    core.info(`Saved ${payload.package}: ${currentKey}, id=${cacheId}`);
    return;
  }

  throw new Error(`Unknown cache operation: ${payload.operation}`);
};
