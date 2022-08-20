#!/bin/bash
pdftoppm -f $2 -l $2 $1 .prefix
draw .prefix*$2*
