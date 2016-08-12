set -euo pipefail

FILENAME="$1"
TRIMMED=$(echo $FILENAME | cut -f 1 -d '.')
HEADER="$TRIMMED.h"
SOURCE="$TRIMMED.cpp"
IDENTIFIER=$(basename $TRIMMED)

cat <<EOF > "$HEADER"
#include <string>

namespace ploy
{

extern const std::string $IDENTIFIER;

}
EOF

cat <<EOF > "$SOURCE"
#include "$(basename $HEADER)"

#include <string>

namespace ploy
{

const std::string $IDENTIFIER =
$(sed 's/\(.*\)/  "\1\\n" \\/g' $FILENAME)
  ;

}
EOF
