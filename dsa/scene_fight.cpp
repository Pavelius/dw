#include "main.h"

static bool melee(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(!player.is(Weapon))
		return false;
	if(run) {
		sc.charge(player);
		auto fighting = player.getfighting();
		if(fighting)
			player.attack(*fighting);
	}
	return true;
}

static bool range(const scene::action& ac, scene& sc, creature& player, bool run) {
	return false;
}

static bool runaway(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(player.is(Fleeing))
		return false;
	if(run) {
		player.say(" - �� ��� ������, � �� ���� �������!! - ��������%� %����� � �����%��� �� ����.");
		player.set(Fleeing);
	}
	return true;
}

static bool isready(const creature& e) {
	return e.isready();
}

static bool iswounded(const creature& e) {
	return e.get(LE) < e.getmaximum(LE);
}

static bool balsam_saladum(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(!player.iscaster())
		return false;
	creaturea source = sc.getcreatures();
	source.remove(Hostile);
	source.match(isready);
	source.match(iswounded);
	if(!source)
		return false;
	if(run) {
		auto p = source.choose("���� [%1] ����� ���������?", player.getname());
		auto m = p->getmaximum(LE) - p->get(LE);
		if(m > player.get(AE))
			m = player.get(AE);
		while(m > 0) {
			an.add(m, "��������� [%1i] ����� �������� �������", m);
			m = m / 2;
		}
		if(!an)
			return false;
		m = an.choosev(true, false, false, "������� ����� ������ ���������� ��������?");
		if(!player.cast(m, 0, " - ������� ��������, ���� ��������! - ������ ������%� %����� ������������� ������ � %���������."))
			return false;
		p->heal(m);
	}
	return true;
}

static bool fulminicktus_donnerkeil(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(!player.iscaster())
		return false;
	creaturea source = sc.getcreatures();
	source.match(Hostile);
	source.match(isready);
	if(!source)
		return false;
	if(run) {
		auto p = source.choose("������� ���� ����������", player.getname());
		auto m = dicei::roll(W3p0) + player.get(Level);
		if(m > p->get(LE))
			m = p->get(LE);
		if(!player.cast(m, 0, " - ������������ ���������!! - ����������%� %����� �������� ����� ����� � ����������� �����."))
			return false;
		player.act(*p, "�� ������ ������� ���������� ���, ������� ������� %���������.");
		p->damage(m, true);
	}
	return true;
}

static bool horriphbus_schreckenspein(const scene::action& ac, scene& sc, creature& player, bool run) {
	if(!player.iscaster())
		return false;
	auto cost = 7;
	auto cost_max = player.get(AE);
	if(cost_max < cost)
		return false;
	creaturea source = sc.getcreatures();
	source.match(Hostile);
	source.match(isready);
	if(!source)
		return false;
	if(run) {
		source.choose(1, cost_max / cost, "��������� �������� [%1i] ������, �� ������� ������ ������� ����.", cost_max / cost);
		auto m = cost * source.getcount();
		if(!player.cast(m, 0, " - �� ������� ���� ���� ���������� � ������ �����!! - ��������%� �������� ������� %����� ������ ���� ��� �������."))
			return false;
		for(auto id : source) {
			auto& e = source.get(id);
			if(!e.roll(Courage)) {
				static const char* text[] = {"����� ���� %����� ������%��� ������ �����.",
					"����������� ����� %����� ���������%��� � �����%��� �� ����.",
				};
				e.act(maprnd(text));
				e.set(Fleeing);
			}
		}
	}
	return true;
}

static scene::action actions[] = {{melee, "��������� ����� � ������� ���"},
{range, "�������� �� �����"},
{runaway, "������ ������ ��� ����� ������"},
{balsam_saladum, "��������� �������� ����������� [�������� �������]"},
{fulminicktus_donnerkeil, "��������� ����� ����������� [��������]"},
{horriphbus_schreckenspein, "�������� ����� ������� ����������� [�����]"},
};

class scene_combat : logs::panel {
	scene&		sc;
public:
	scene_combat(scene& sc) : sc(sc) {}
	void print(stringbuilder& sb) override {
		for(auto id : sc.getcreatures()) {
			auto& e = sc.getcreature(id);
			sb.addsep('\n'); e.status(sb);
		}
	}
};

void scene::fight() {
	scene_combat sc(*this);
	makeorder();
	while(ishostile()) {
		for(auto id : creatures) {
			auto& e = getcreature(id);
			if(!e.isready())
				continue;
			sb.addsep('\n');
			e.testfighting();
			if(e.isplayer()) {
				ask(e, actions);
				choose(e);
			} else {
				charge(e);
				auto fighting = e.getfighting();
				if(fighting)
					e.attack(*fighting);
			}
		}
		an.add(1, "��������� ����� ���");
		an.choose();
	}
}