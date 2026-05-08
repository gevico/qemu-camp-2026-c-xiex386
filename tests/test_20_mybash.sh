THIS_DIR="$(dirname "$0")"
MYBASH_PATH=$(cd "${THIS_DIR}" && pwd)/mybash_cmd.sh

cd "${THIS_DIR}/../exercises/20_mybash"
bin/mybash "$MYBASH_PATH"
