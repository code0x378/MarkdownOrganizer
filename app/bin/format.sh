 #!/bin/bash
cd ..
astyle --options="etc/astyle.conf" --suffix=none --recursive "src/*.cpp"  "src/*.h" 