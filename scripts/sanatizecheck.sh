#!/usr/bin/env bash

valgrind -s --leak-check=full --track-origins=yes ./build/lista_telefonica
