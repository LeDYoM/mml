#include "../include/graph/bmfont.h"
#include <fstream>
#include <sstream> 
#include "../include/graph/BMText.h"
#include "../mlprivcconfig.h"
#include "../openglPriv.h"

namespace ml
{
	namespace graph
	{
		BMFont::BMFont()
		{
			SetColor(Color(1.0f, 1.0f, 1.0f, 1.0f));
			fblend = 0;
			chars.resize(256);
		}

		BMFont::~BMFont()
		{
		}

		// Small help parser funcs
		std::string getStr(const std::string &read)
		{
			std::string result;

			for (char ch : read)
			{
				if (ch != '"')
				{
					result.push_back(ch);
				}
			}
			return result;
		}
		void filterStr(std::stringstream &LineStream, std::string &Value)
		{
			bool doNext = true;
			do
			{
				int first_ = Value.find_first_of('\"');
				int last_ = Value.find_last_of('\"');
				doNext = (first_ > -1 && first_ == last_);
				if (doNext)
				{
					std::string readTemp;
					LineStream >> readTemp;
					Value += " " + readTemp;
				}
			} while (doNext);
		}
		bool BMFont::ParseFont(const std::string&fontfile)
		{
			std::ifstream Stream(fontfile);
			std::string Line, Read, Key, Value;
			std::size_t i;
			s32 first, second, amount;

			KearningInfo K;
			CharDescriptor C;

			while (!Stream.eof())
			{
				std::stringstream LineStream;
				std::getline(Stream, Line);
				LineStream << Line;

				//read the line's type
				LineStream >> Read;
				if (Read == "common")
				{
					//this holds common data
					while (!LineStream.eof())
					{
						std::stringstream Converter;
						LineStream >> Read;
						i = Read.find('=');
						Key = Read.substr(0, i);
						Value = Read.substr(i + 1);

						//assign the correct value
						Converter << Value;
						if (Key == "lineHeight")
						{
							Converter >> lineHeight;
						}
						else if (Key == "base")
						{
							Converter >> base;
						}
						else if (Key == "scaleW")
						{
							Converter >> size.x;
						}
						else if (Key == "scaleH")
						{
							Converter >> size.y;
						}
						else if (Key == "pages")
						{
							Converter >> pages;
						}
						else if (Key == "outline")
						{
							Converter >> outline;
						}
					}
				}
				else if (Read == "page")
				{
					//this holds common data
					while (!LineStream.eof())
					{
						std::stringstream Converter;
						LineStream >> Read;
						i = Read.find('=');
						Key = Read.substr(0, i);
						Value = Read.substr(i + 1);
						u32 id(0);

						filterStr(LineStream, Value);

						//assign the correct value
						Converter << Value;
						if (Key == "id")
						{
							Converter >> id;
							pagesData.resize(id+1);
						}
						else if (Key == "file")
						{
							pagesData[id].file = getStr(Value);
						}
					}
				}
				else if (Read == "info")
				{
					//this holds info font data
					while (!LineStream.eof())
					{
						std::stringstream Converter;
						LineStream >> Read;
						i = Read.find('=');
						Key = Read.substr(0, i);
						Value = Read.substr(i + 1);

						filterStr(LineStream, Value);
						Converter << Value;
						if (Key == "face")
						{
							fInfo.face = getStr(Value);
						}
						else if (Key == "size")
						{
							Converter >> fInfo.size;
						}
						else if (Key == "bold")
						{
							Converter >> fInfo.bold;
						}
						else if (Key == "italic")
						{
							Converter >> fInfo.italic;
						}
						else if (Key == "charset")
						{
							fInfo.charset = getStr(Value);
						}
						else if (Key == "unicode")
						{
							Converter >> fInfo.unicode;
						}
						else if (Key == "stretchH")
						{
							Converter >> fInfo.stretchH;
						}
						else if (Key == "smooth")
						{
							Converter >> fInfo.smooth;
						}
						else if (Key == "aa")
						{
							Converter >> fInfo.aa;
						}
						else if (Key == "padding")
						{
							std::string temp;
							std::getline(Converter, temp, ',');
							fInfo.padding.x = std::atoi(temp.c_str());
							std::getline(Converter, temp, ',');
							fInfo.padding.y = std::atoi(temp.c_str());
							std::getline(Converter, temp, ',');
							fInfo.padding.x2 = std::atoi(temp.c_str());
							std::getline(Converter, temp, ',');
							fInfo.padding.y2 = std::atoi(temp.c_str());
						}
						else if (Key == "spacing")
						{
							std::string temp;
							std::getline(Converter, temp, ',');
							fInfo.spacing.x = std::atoi(temp.c_str());
							std::getline(Converter, temp, ',');
							fInfo.spacing.y = std::atoi(temp.c_str());
						}
						else if (Key == "outline")
						{
							Converter >> fInfo.outline;
						}
					}
				}
				else if (Read == "char")
				{
					//This is data for each specific character.
					int CharID = 0;

					while (!LineStream.eof())
					{
						std::stringstream Converter;
						LineStream >> Read;
						i = Read.find('=');
						Key = Read.substr(0, i);
						Value = Read.substr(i + 1);

						//Assign the correct value
						Converter << Value;
						if (Key == "id")
						{
							Converter >> CharID;
						}
						else if (Key == "x")
						{
							Converter >> C.position.x;
						}
						else if (Key == "y")
						{
							Converter >> C.position.y;
						}
						else if (Key == "width")
						{
							u16 temp;
							Converter >> temp;
							C.position.setWidth(temp);
						}
						else if (Key == "height")
						{
							u16 temp;
							Converter >> temp;
							C.position.setHeight(temp);
						}
						else if (Key == "xoffset")
						{
							Converter >> C.offset.x;
						}
						else if (Key == "yoffset")
						{
							Converter >> C.offset.y;
						}
						else if (Key == "xadvance")
						{
							Converter >> C.xadvance;
						}
						else if (Key == "page")
						{
							Converter >> C.page;
						}
					}
					if (CharID < 256)
						chars[CharID] = C;

				}
				else if (Read == "kernings")
				{
					while (!LineStream.eof())
					{
						std::stringstream Converter;
						LineStream >> Read;
						i = Read.find('=');
						Key = Read.substr(0, i);
						Value = Read.substr(i + 1);

						//assign the correct value
						Converter << Value;
						//				if( Key == "count" )
						//				     {Converter >> KernCount; }
					}
				}

				else if (Read == "kerning")
				{
					while (!LineStream.eof())
					{
						std::stringstream Converter;
						LineStream >> Read;
						i = Read.find('=');
						Key = Read.substr(0, i);
						Value = Read.substr(i + 1);

						Converter << Value;
						if (Key == "first")
						{
							Converter >> first;
						}

						else if (Key == "second")
						{
							Converter >> second;
						}

						else if (Key == "amount")
						{
							Converter >> amount;
						}
					}
					CharDescriptor &ch = chars[first];
					ch.kearn.push_back(KearningInfo(second, amount));
				}
			}

			Stream.close();
			return true;
		}

		float BMFont::stringWidth(const std::string&string,bool useKern) const
		{
			f32 total = 0.0f;
			for (u32 i = 0; i < string.size(); i++)
			{
				const CharDescriptor *f = &(chars[string[i]]);
				total += f->xadvance;

				if (useKern && string.size() > 1 && i < (string.size() - 1))
				{
					total += (f32)(f->GetKerningPair(string[i + 1]));
				}

			}

			return total;
		}


		bool  BMFont::Load(const std::string &baseFile)
		{
			std::string fontfile(baseFile + ".fnt");
			std::string texturefile(baseFile + ".png");
			LOG_PRIVATE_DEBUG("Starting to Parse Font " << fontfile);
			ParseFont(fontfile);
			LOG_PRIVATE_DEBUG("Finished Parsing Font " << fontfile);
			LOG_PRIVATE_DEBUG("Loading pages. Number of pages: " << pagesData.size());

			for (u32 i = 0; i < pagesData.size(); ++i)
			{
				pagesData[i].image.Load(pagesData[i].file);
				pagesData[i].texture.Load(pagesData[i].image);
			}
			LOG_PRIVATE_DEBUG("Page(s) loaded");

			return true;
		}
	}
}
