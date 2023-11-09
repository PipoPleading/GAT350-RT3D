#include "ResourceEditor.h"
#include "ResourceManager.h"
#include "Renderer/Material.h"
#include "Renderer/GUI.h"
#include <algorithm>

namespace nc
{
	void ResourceEditor::ProcessGui()
	{
		ImGui::Begin("Resources");
		auto resources = ResourceManager::Instance().GetAllOfType<Material>();
		for (auto& resource : resources)
		{
			if (ImGui::Selectable(resource->name.c_str(), resource->guiSelect))
			{
				// set all actors gui to false
				std::for_each(resources.begin(), resources.end(), [](auto& a) { a->guiSelect = false; });
				// set selected actor gui to true
				resource->guiSelect = true;
			}
		}

		ImGui::Separator();
		auto iter = std::find_if(resources.begin(), resources.end(), [](auto& a) { return a->guiSelect; });
		if (iter != resources.end())
		{
			ImGui::TextColored({ 0, 1, 0, 1 }, "%s", (*iter)->GetClassName());
			ImGui::Text("Name: %s", (*iter)->name.c_str());

			(*iter)->ProcessGui();
		}
		ImGui::End();
	}
}
