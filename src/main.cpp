#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
	
	struct Fields {
		int m_lastObjectCount = 0;
		float m_lastObjectX = 0.f;
	};

	void checkForObjectChange(float dt) {
		auto fields = m_fields.self();

		int last = fields->m_lastObjectCount;
		int cur = m_editorLayer->m_objectCount;

		if (last != cur) {
			fields->m_lastObjectX = m_editorLayer->getLastObjectX();
			updateSlider();
		}
	
		fields->m_lastObjectCount = m_editorLayer->m_objectCount;
    }

    bool init(LevelEditorLayer* editorLayer) {
		if (!EditorUI::init(editorLayer)) return false;
        schedule(schedule_selector(MyEditorUI::checkForObjectChange));
		return true;
	}

    void sliderChanged(cocos2d::CCObject*) {
		auto fields = m_fields.self();

		float maxX = (fields->m_lastObjectX + 300) * m_editorLayer->m_objectLayer->getScale();
		float x = -(maxX * m_positionSlider->getThumb()->getValue()) + 100;
		float y = m_editorLayer->m_objectLayer->getPositionY();
		m_editorLayer->m_objectLayer->setPosition({x, y});
		constrainGameLayerPosition(-100, -100);
	}

	void updateSlider() {
		auto fields = m_fields.self();

		float maxX = (fields->m_lastObjectX + 300) * m_editorLayer->m_objectLayer->getScale();
		float x = -m_editorLayer->m_objectLayer->getPositionX() + 100;
		float pos = std::clamp(x / maxX, 0.0f, 1.0f);
		m_positionSlider->setValue(pos);
	}

};