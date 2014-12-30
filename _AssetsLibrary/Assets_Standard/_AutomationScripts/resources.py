#!/usr/bin/env python
# -*- coding: utf-8 -*-
# resources.py
# Author: Painache

import os,sys

# resources path
rs_path = "../Assets/Assets"
# classes path
output_path = "../../../Scripts/Scripts"
# resource define
js_file = output_path + "/Resources.js"

varname_list = []

def processDirectory ( args, dirname, filenames ):
    print 'Directory',dirname
    if (dirname.split('/')[-1] == "HD"):
        # print 'Directory',dirname
        for filename in filenames:
            
            if (filename[0:3] == "BMF"):
                
                if (filename.split('.')[-1] == "plist"):

                    varname = "RES_BMF_PLIST"
                    varname_list.append(varname)
                    f.write("var " + varname + " = '" + filename + "';" + "\n")

                if (filename.split('.')[-1] == "png"):

                    varname = "RES_BMF_PNG"
                    varname_list.append(varname)
                    f.write("var " + varname + " = '" + filename + "';" + "\n")

                if (filename.split('.')[-1] == "fnt"):
                    print filename
                    varname = "RES_BMF_FNT_" + filename.split('.')[0][4:]
                    varname_list.append(varname)
                    f.write("var " + varname + " = '" + filename + "';" + "\n")

            if (filename[0:3] == "TEX"):
                
                if (filename.split('.')[-1] == "plist"):

                    varname = "RES_TEX_PLIST_" + filename.split('.')[0][4:]
                    varname_list.append(varname)
                    f.write("var " + varname + " = '" + filename + "';" + "\n")

                if (filename.split('.')[-1] == "png"):

                    varname = "RES_TEX_PNG_" + filename.split('.')[0][4:]
                    varname_list.append(varname)
                    f.write("var " + varname + " = '" + filename + "';" + "\n")

    # if (dirname.split('/')[-1] == "CCBI"):
    if "CCBI" in dirname :
        for filename in filenames:
            if (filename.split('.')[-1] == "ccbi"):
                varname = "RES_CCBI_" + filename.split('.')[0]
                varname = varname.replace("-", "_")
                varname_list.append(varname)
                f.write("var " + varname + " = '" + dirname.replace("../", "").replace("Assets/Assets", "Assets") + "/" + filename + "';" + "\n")

        f.write("\n")

    if (dirname.split('/')[-1] == "BGM"):
        f.write("\n")
        for filename in filenames:
            if filename.split('.')[0] != '': #ignore .DS_store
                varname = "RES_BGM_" + filename.split('.')[0]
                varname = varname.replace("-", "_")
                print varname
                varname_list.append(varname)
                f.write("var " + varname + " = '" + dirname.replace("../", "").replace("Assets/Assets", "Assets") + "/" + filename + "';" + "\n")
        
    if (dirname.split('/')[-1] == "SFX"):
        f.write("\n")
        for filename in filenames:
            if filename.split('.')[0] != '': #ignore .DS_store
                varname = "RES_SFX_" + filename.split('.')[0]
                varname = varname.replace("-", "_")
                print varname
                varname_list.append(varname)
                f.write("var " + varname + " = '" + dirname.replace("../", "").replace("Assets/Assets", "Assets") + "/" + filename + "';" + "\n")

    if "TMX" in dirname :
        f.write("\n")
        for filename in filenames:
            if (filename.split('.')[-1] == "tmx"):
                varname = "RES_TMX_" + filename.split('.')[0]
                varname = varname.replace("-", "_")
                varname_list.append(varname)
                f.write("var " + varname + " = '" + dirname.replace("../", "").replace("Assets/Assets", "Assets") + "/" + filename + "';" + "\n")

            if (filename.split('.')[-1] == "tsx"):
                varname = "RES_TSX_" + filename.split('.')[0]
                varname = varname.replace("-", "_")
                varname_list.append(varname)
                f.write("var " + varname + " = '" + dirname.replace("../", "").replace("Assets/Assets", "Assets") + "/" + filename + "';" + "\n")
    
    if "Data" in dirname:
        f.write("\n")
        for filename in filenames:
            if filename.split('.')[0] != '': #ignore .DS_store
                if (filename.split('.')[-1] == "json"):
                    varname = "RES_JSON_" + filename.split('.')[0]
                    varname = varname.replace("-", "_")
                    print varname
                    varname_list.append(varname)
                    f.write("var " + varname + " = '" + dirname.replace("../", "").replace("Assets/Assets", "Assets") + "/" + filename + "';" + "\n")
                if (filename.split('.')[-1] == "c"):
                    varname = "RES_C_" + filename.split('.')[0]
                    varname = varname.replace("-", "_")
                    print varname
                    varname_list.append(varname)
                    f.write("var " + varname + " = '" + dirname.replace("../", "").replace("Assets/Assets", "Assets") + "/" + filename + "';" + "\n")

        f.write("\n")


def generate_js():

    os.path.walk(rs_path, processDirectory, None )

    f.write("\n")
    f.write("var g_resources = [\n")
    for varname in varname_list:
        # print varname + "\n"
        f.write("\t{src:" + varname + "},\n")

    f.write("];")
    

if os.path.isfile(js_file):
    os.remove(js_file)
f = file(js_file, 'w')
   
generate_js()

f.close()

print("Done.")


