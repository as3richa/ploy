set -euo pipefail

FILENAME="$1"
BUILDDIR="$2"
TRIMMED=$(basename $FILENAME | cut -f 1 -d '.')
HEADER="$BUILDDIR/$TRIMMED.h"
SOURCE="$BUILDDIR/$TRIMMED.cpp"
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
