#!/bin/bash

echo "# AUTHORS" > AUTHORS

git log --format="%aN <%aE>" | sort -u >> AUTHORS
