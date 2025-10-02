import sys
import pytest

#If using 'bazel test //*test_dir*'
if __name__ == "__main__":
    args = sys.argv[1:]
    sys.exit(pytest.main(args))