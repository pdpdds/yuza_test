#include <minwindef.h>
#include <minwinconst.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <winapi.h>
#include <systemcall_impl.h>
#include "GUIConsoleFramework.h"

#include <fontconfig/fontconfig.h>

int main_impl(int argc, char** argv)
{
	FcConfig* config = FcInitLoadConfigAndFonts();
	//make pattern from font name
	FcPattern* pat = FcNameParse((const FcChar8*)"Arial");
	FcConfigSubstitute(config, pat, FcMatchPattern);
	FcDefaultSubstitute(pat);
	char* fontFile; //this is what we'd return if this was a function
	// find the font
	FcResult result;
	FcPattern* font = FcFontMatch(config, pat, &result);
	if (font)
	{
		FcChar8* file = NULL;
		if (FcPatternGetString(font, FC_FILE, 0, &file) == FcResultMatch)
		{
			//we found the font, now print it.
			//This might be a fallback font
			fontFile = (char*)file;
			printf("%s\n", fontFile);
		}
	}
	FcPatternDestroy(pat);
	return 0;
}

int main(int argc, char** argv)
{
	GUIConsoleFramework framework;
	framework.Run(argc, argv, main_impl);
}