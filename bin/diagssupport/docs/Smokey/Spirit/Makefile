.PHONY: default clean mostlyclean

COMMON_DIR = ../../LaTeX/
PACKAGES = \
	$(COMMON_DIR)Smokey.sty \
	$(COMMON_DIR)mylistings/listings.sty

PROJECT = SmokeyManual
VERSION = Spirit
ASSETS = \
	ScreenConnectToBrick.pdf \
	ScreenFail.pdf \
	ScreenPass.pdf \
	ScreenRunning-Cinnamon.pdf \
	SmokeySystemDiagram2-Portrait.pdf

export TEXINPUTS := $(TEXINPUTS):$(COMMON_DIR)
LATEX = xelatex '\gdef\CommonDir{$(COMMON_DIR)}\input{$1}' -o $2

default: $(PROJECT)-$(VERSION).pdf

$(PROJECT)-$(VERSION).pdf: $(PROJECT).pdf
	mv $< $@

$(PROJECT).pdf: \
	$(PROJECT).tex \
	$(PROJECT)Title.tex \
	$(PROJECT)Body.tex \
	$(ASSETS) \
	$(PACKAGES)

%.pdf: %.tex
	set -o errexit; \
	OldAuxHash=$$(md5 $(dir $@)/*.aux 2>/dev/null || true); \
	$(call LATEX,$<,$@); \
	NewAuxHash=$$(md5 $(dir $@)/*.aux 2>/dev/null || true); \
	if [ "$$OldAuxHash" != "$$NewAuxHash" ]; then \
		echo "******************************************************************************"; \
		$(call LATEX,$<,$@); \
	fi

clean: mostlyclean
	rm -f $(PROJECT)-$(VERSION).pdf

mostlyclean:
	rm -f *~
	rm -f *.aux *.log *.toc *.lof *.lot *.out
