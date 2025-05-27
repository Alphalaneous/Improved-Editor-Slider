#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(MyEditorUI, EditorUI) {
	
    void sliderChanged(cocos2d::CCObject*) {
		float maxX = (m_editorLayer->getLastObjectX() + 300) * m_editorLayer->m_objectLayer->getScale();
		float x = -(maxX * m_positionSlider->getThumb()->getValue()) + 100;
		float y = m_editorLayer->m_objectLayer->getPositionY();
		m_editorLayer->m_objectLayer->setPosition({x, y});
		constrainGameLayerPosition(x, y);
	}

	void updateSlider() {
		float maxX = (m_editorLayer->getLastObjectX() + 300) * m_editorLayer->m_objectLayer->getScale();
		float x = -m_editorLayer->m_objectLayer->getPositionX() + 100;
		float pos = std::clamp(x / maxX, 0.0f, 1.0f);
		m_positionSlider->setValue(pos);
	}

};