#!/usr/bin/env python3
"""
Main entry point for English Learning App
"""

import sys
import os

# Add current directory to path for module imports
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from python_gui.main import EnglishAppGUI
from PyQt5.QtWidgets import QApplication

if __name__ == "__main__":
    app = QApplication(sys.argv)
    gui = EnglishAppGUI()
    gui.show()
    sys.exit(app.exec_())