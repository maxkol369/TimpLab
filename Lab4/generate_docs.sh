#!/bin/bash
echo "=== Генерация документации для TIMPLABY laba4 ==="

# Устанавливаем зависимости (если нужно)
sudo apt-get install doxygen graphviz texlive-latex-base texlive-latex-extra -y

# Создаем конфигурационный файл Doxygen
cat > Doxyfile << 'CONFIG'
PROJECT_NAME = "TIMPLABY Laba4"
PROJECT_NUMBER = "4"
PROJECT_BRIEF = "Лабораторная работа по ТИМП"
OUTPUT_DIRECTORY = documentation
INPUT = .
FILE_PATTERNS = *.h *.hpp *.cpp *.c *.cc *.cxx *.py
RECURSIVE = YES
EXTRACT_ALL = YES
EXTRACT_PRIVATE = YES
EXTRACT_STATIC = YES
GENERATE_HTML = YES
GENERATE_LATEX = YES
HTML_OUTPUT = html
LATEX_OUTPUT = latex
CONFIG

echo "Генерация документации..."
doxygen Doxyfile

echo "Генерация PDF..."
cd documentation/latex
make

if [ -f "refman.pdf" ]; then
    cp refman.pdf ../../TIMPLABY_laba4_documentation.pdf
    echo "✓ PDF создан: TIMPLABY_laba4_documentation.pdf"
else
    echo "✗ Ошибка создания PDF"
    echo "Пробуем альтернативный способ..."
    cd ../..
    sudo apt-get install wkhtmltopdf -y
    wkhtmltopdf --enable-local-file-access documentation/html/index.html TIMPLABY_laba4_documentation.pdf
fi

echo "Готово!"
