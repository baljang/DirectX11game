﻿#include "pch.h"
#include "Animation.h"
#include "Texture.h"

Animation::Animation() : Super(ResourceType::Animation)
{
}

Animation::~Animation()
{
}

void Animation::Load(const wstring& path)
{
	tinyxml2::XMLDocument doc;

	string pathStr(path.begin(), path.end()); 
	XMLError error = doc.LoadFile(pathStr.c_str());
	assert(error == XMLError::XML_SUCCESS); 

	XmlElement* root = doc.FirstChildElement(); 
	string nameStr = root->Attribute("Name"); 
	_name = wstring(nameStr.begin(), nameStr.end()); 

	_loop = root->BoolAttribute("Loop"); 
	_path = path; 

	// Load Texture
	
	XmlElement* node = root->FirstChildElement();
	for (; node != nullptr; node = node->NextSiblingElement())
	{
		Keyframe keyframe; 

		keyframe.offset.x = node->FloatAttribute("OffsetX"); 
		keyframe.offset.y = node->FloatAttribute("OffsetY"); 
		keyframe.size.x = node->FloatAttribute("SizeX"); 
		keyframe.size.y = node->FloatAttribute("SizeY"); 
		keyframe.time = node->FloatAttribute("Time"); 

		AddKeyframe(keyframe); 
	}
}

void Animation::Save(const wstring& path)
{
	tinyxml2::XMLDocument doc; 

	// node를 element라고 부른다고 생각하면 된다. 
	XMLElement* root = doc.NewElement("Animation"); // 노드 만들기
	doc.LinkEndChild(root); // 만들어준 노드를 문서에 추가 

	string nameStr(GetName().begin(), GetName().end()); 
	root->SetAttribute("Name", nameStr.c_str()); // key값, value로 정보를 넣어 주는 거 Name = "SnakeAnim"
	root->SetAttribute("Loop",_loop); 
	root->SetAttribute("TexturePath", "TODO"); // 나중에 경로를 넣어 줄 수 있다.

	// root 산하의 여러 노드를 만들어 준다
	for (const auto& keyframe : _keyframes)
	{
		XMLElement* node = doc.NewElement("Keyframe"); 
		root->LinkEndChild(node); 

		node->SetAttribute("OffsetX", keyframe.offset.x); 
		node->SetAttribute("OffsetY", keyframe.offset.y); 
		node->SetAttribute("SizeX", keyframe.size.x); 
		node->SetAttribute("SizeY", keyframe.size.y); 
		node->SetAttribute("Time", keyframe.time); 
	}

	string pathStr(path.begin(), path.end()); 
	auto result = doc.SaveFile(pathStr.c_str());
	assert(result == XMLError::XML_SUCCESS);
}

Vec2 Animation::GetTextureSize()
{
	return _texture->GetSize();
}

const Keyframe& Animation::GetKeyframe(int32 index)
{
	return _keyframes[index];
}

int32 Animation::GetKeyframeCount()
{
	return static_cast<int32>(_keyframes.size()); 
}

void Animation::AddKeyframe(const Keyframe& keyframe)
{
	_keyframes.push_back(keyframe); 
}


